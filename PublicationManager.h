#ifndef PUBLICATIONMANAGER_H
#define PUBLICATIONMANAGER_H

#include "Publication.h"
#include <vector>
#include <string>

class PublicationManager {
    std::vector<Publication> publications;

public:
    void addPublication(const Publication& publication);
    std::vector<Publication> findPublicationsByAuthor(const std::string& authorName) const;
    double calculateAverageCoAuthors(const std::string& authorName) const;
    const std::vector<Publication>& getPublications() const { return publications; }
};

#endif // PUBLICATIONMANAGER_H
