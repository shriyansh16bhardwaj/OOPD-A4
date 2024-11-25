#include <fstream>
#include <iostream>
#include <unordered_set>
#include <sstream>
#include <cassert>
#include <set>
#include <vector>
#include "PublicationManager.h"
#include "Author.h"
#include "Publication.h"
#include <algorithm>

int parseBib(const std::string& filename, PublicationManager& manager, const std::string& instituteName, const std::vector<std::string>& faculty) {
    std::ifstream bibFile(filename);

    if (!bibFile) {
        std::cerr << "Error: Could not open " << filename << " file.\n";
        return 0; // Return 0 if the file cannot be opened
    }

    std::string line, entryType, entryKey;
    bool insideEntry = false;

    // Variables to hold parsed data
    std::string title, venue, doi, authorStr;
    int year = 0;
    std::vector<Author> authors;

    // Parse the .bib file line by line
    while (getline(bibFile, line)) {
        // Remove leading and trailing spaces
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (line.empty()) continue;

        // Identify the start of a new entry
        if (line[0] == '@') {
            size_t startType = line.find_first_of('@') + 1;
            size_t endType = line.find_first_of('{', startType);
            entryType = line.substr(startType, endType - startType);
            entryKey = line.substr(endType + 1, line.find_first_of(',') - endType - 1);

            insideEntry = true;

            // Reset the parsed data for the new entry
            title = venue = doi = authorStr = "";
            year = 0;
            authors.clear();
            continue;
        }

        if (insideEntry) {
            if (line[0] == '}') {
                // End of the current entry
                insideEntry = false;

                // Parse the author string into a list of Author objects
                if (!authorStr.empty()) {
                    // Replace " and " with ";" for easier splitting
                    while (authorStr.find(" and ") != std::string::npos) {
                        authorStr.replace(authorStr.find(" and "), 5, ";");
                    }

                    std::stringstream ss(authorStr);
                    std::string authorName;
                    while (getline(ss, authorName, ';')) {
                        // Split "LastName, FirstName" into "FirstName LastName"
                        size_t commaPos = authorName.find(',');
                        if (commaPos != std::string::npos) {
                            std::string lastName = authorName.substr(0, commaPos);
                            std::string firstName = authorName.substr(commaPos + 1);

                            // Trim spaces
                            lastName.erase(0, lastName.find_first_not_of(" "));
                            lastName.erase(lastName.find_last_not_of(" ") + 1);
                            firstName.erase(0, firstName.find_first_not_of(" "));
                            firstName.erase(firstName.find_last_not_of(" ") + 1);

                            // Convert to "FirstName LastName" format
                            authorName = firstName + " " + lastName;
                        }

                        // Check if the author already exists in the vector
                        auto it = std::find_if(authors.begin(), authors.end(), [&](const Author& a) {
                            return a.getName() == authorName; // Compare names
                        });

                        // If author does not already exist, add to vector
                        if (it == authors.end()) {
                            authors.emplace_back(authorName, instituteName);
                        } else {
                            std::cout << "Duplicate author \"" << authorName << "\" ignored.\n";
                        }
                    }
                }

                // Check if any author is in the faculty list
                bool isFacultyAuthor = false;
                for (const auto& author : authors) {
                    if (std::find(faculty.begin(), faculty.end(), author.getName()) != faculty.end()) {
                        isFacultyAuthor = true;
                        break;
                    }
                }

                // Add publication to manager only if at least one author is in faculty
                if (isFacultyAuthor) {
                    Publication publication(title, venue, year, authors, doi, authorStr);

                    manager.addPublication(publication);

                    // Print the authors along with the publication being added
                    std::cout << "Publication \"" << title << "\" added to the manager.\n";
                    std::cout << "Authors: ";
                    for (const auto& author : authors) {
                        std::cout << author.getName() << ", ";
                    }
                    std::cout << std::endl;
                } else {
                    std::cout << "Publication \"" << title << "\" not added (no faculty author).\n";
                    std::cout << "Authors: ";
                    for (const auto& author : authors) {
                        std::cout << author.getName() << ", ";
                    }
                    std::cout << std::endl;
                }

                continue;
            }

            // Parse key-value pairs in the entry
            size_t delimiter = line.find('=');
            if (delimiter != std::string::npos) {
                std::string key = line.substr(0, delimiter);
                std::string value = line.substr(delimiter + 1);

                // Remove leading/trailing spaces and curly braces
                key.erase(0, key.find_first_not_of(" \t"));
                key.erase(key.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t{"));
                value.erase(value.find_last_not_of(" \t},") + 1);

                // Assign values to variables based on the key
                if (key == "title") {
                    title = value;
                } else if (key == "venue") {
                    venue = value;
                } else if (key == "year") {
                    year = std::stoi(value);
                } else if (key == "author") {
                    authorStr = value;
                } else if (key == "doi") {
                    doi = value;
                }
            }
        }
    }

    std::cout << "Bib file parsed and manager populated successfully.\n";
    return 1; // Return 1 if parsing and population are successful
}

int main() {
    std::string instituteName = "IIIT-Delhi";
    std::vector<std::string> faculty;

    // Load Faculty from CSV
    std::cout << "Loading faculty data from CSV...\n";
    std::ifstream csvFile("faculty.csv");
    if (!csvFile) {
        std::cerr << "Error: Could not open faculty.csv file.\n";
        return 1;
    }

    std::string line;
    getline(csvFile, line); // Skip header
    while (getline(csvFile, line)) {
        std::istringstream ss(line);
        std::string name, affiliation;
        getline(ss, name, ',');
        faculty.push_back(name);
    }
    csvFile.close();
    std::cout << "Faculty data loaded successfully. Found " << faculty.size() << " faculty members affiliated with " << instituteName << ".\n";

    std::string filename = "publist.bib";

    // Create a manager object
    PublicationManager manager;

    // Parse the .bib file and populate the manager
    int parseResult = parseBib(filename, manager, instituteName, faculty);

    if (parseResult) {
        std::cout << "Parsing completed successfully.\n";

        // Get input from user for author names
        std::cout << "\nEnter author names (comma-separated): ";
        std::string input;
        getline(std::cin, input);

        // Split the input into a list of author names
        std::vector<std::string> queriedAuthors;
        std::stringstream inputSS(input);
        std::string authorName;
        while (getline(inputSS, authorName, ',')) {
            authorName.erase(0, authorName.find_first_not_of(" ")); // Trim leading spaces
            authorName.erase(authorName.find_last_not_of(" ") + 1); // Trim trailing spaces
            queriedAuthors.push_back(authorName);
        }

        // Display publications and calculate the average number of co-authors
        for (const auto& queriedAuthor : queriedAuthors) {
            auto publications = manager.findPublicationsByAuthor(queriedAuthor);

            if (publications.empty()) {
                std::cout << "\nNo publications found for author: " << queriedAuthor << "\n";
                continue;
            }

            std::cout << "\nPublications for Author: " << queriedAuthor << "\n";
            double totalCoAuthors = 0;
            int publicationCount = 0;

            for (const auto& pub : publications) {
                pub.print();
                int coAuthorCount = pub.getAuthors().size() - 1; // Exclude the queried author
                totalCoAuthors += coAuthorCount;
                publicationCount++;
            }

            double averageCoAuthors = (publicationCount > 0) ? (totalCoAuthors / publicationCount) : 0.0;
            std::cout << "Average Number of Co-Authors per Paper: " << averageCoAuthors << "\n";
        }
    } else {
        std::cerr << "Failed to parse the .bib file.\n";
    }

    return 0;
}
