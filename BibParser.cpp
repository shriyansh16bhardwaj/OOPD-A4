#include "BibParser.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cassert>
#include <regex>

std::vector<Publication> BibParser::parse(const std::string& filePath, const std::string& instituteAffiliation) {
    std::vector<Publication> publications;
    std::ifstream file(filePath);

    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open bib file.");
    }

    std::string line, currentEntry;
    std::regex entryRegex(R"(^@\w+\{.*,$)");
    int braceCount = 0;

    while (std::getline(file, line)) {
        if (line.find('{') != std::string::npos) braceCount++;
        if (line.find('}') != std::string::npos) braceCount--;

        currentEntry += line + "\n";

        if (braceCount == 0 && !currentEntry.empty()) {
            assert(std::regex_search(currentEntry, entryRegex) && "Invalid Bib entry format!");

            Publication publication;

            // Parse title
            std::regex titleRegex(R"(title=\{(.*?)\},)");
            std::smatch match;
            if (std::regex_search(currentEntry, match, titleRegex)) {
                publication.setTitle(match[1]);
            }

            // Parse venue
            std::regex venueRegex(R"(venue=\{(.*?)\},)");
            if (std::regex_search(currentEntry, match, venueRegex)) {
                publication.setVenue(match[1]);
            }

            // Parse year
            std::regex yearRegex(R"(year=\{(.*?)\},)");
            if (std::regex_search(currentEntry, match, yearRegex)) {
                publication.setYear(std::stoi(match[1]));
            }

            // Parse DOI
            std::regex doiRegex(R"(doi=\{(.*?)\})");
            if (std::regex_search(currentEntry, match, doiRegex)) {
                publication.setDOI(match[1]);
            }

            // Parse authors
            std::regex authorRegex(R"(author=\{(.*?)\},)");
            if (std::regex_search(currentEntry, match, authorRegex)) {
                std::string authors = match[1];
                std::stringstream authorStream(authors);
                std::string author;

                bool hasInstituteAffiliation = false;
                while (std::getline(authorStream, author, ',')) {
                    std::string trimmed = std::regex_replace(author, std::regex("^\\s+|\\s+$"), "");
                    if (trimmed.find(instituteAffiliation) != std::string::npos) {
                        hasInstituteAffiliation = true;
                    }
                    publication.addAuthor(Author(trimmed, "Affiliation TBD"));
                }
                assert(hasInstituteAffiliation && "No author with the institute's affiliation found!");
            }

            publications.push_back(publication);
            currentEntry.clear();
        }
    }

    return publications;
}
