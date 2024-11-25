#include "PublicationManager.h"
#include <numeric>

void PublicationManager::addPublication(const Publication& publication) {
    publications.push_back(publication);
}

std::vector<Publication> PublicationManager::findPublicationsByAuthor(const std::string& authorName) const {
    std::vector<Publication> result;
    for (const auto& pub : publications) {
        for (const auto& author : pub.getAuthors()) {
            if (author.getName() == authorName) {
                result.push_back(pub);
                break;
            }
        }
    }
    return result;
}

double PublicationManager::calculateAverageCoAuthors(const std::string& authorName) const {
    std::vector<Publication> authorPublications = findPublicationsByAuthor(authorName);
    if (authorPublications.empty()) return 0.0;

    int totalCoAuthors = 0;
    for (const auto& pub : authorPublications) {
        totalCoAuthors += pub.getAuthors().size() - 1;
    }
    return static_cast<double>(totalCoAuthors) / authorPublications.size();
}
