#ifndef PUBLICATION_H
#define PUBLICATION_H

#include <string>
#include <vector>
#include "Author.h"

class Publication {
private:
    std::string title;
    std::string venue;
    int year;
    std::string doi;
    std::vector<Author> authors;
    std::string authorStr; // Additional field to match constructor argument

public:
    // Constructors
    Publication() = default;
    Publication(const std::string& title, const std::string& venue, int year,
                const std::vector<Author>& authors, const std::string& doi, 
                const std::string& authorStr);

    // Setters
    void setTitle(const std::string& title);
    void setVenue(const std::string& venue);
    void setYear(int year);
    void setDOI(const std::string& doi);

    // Getters
    const std::string& getTitle() const;
    const std::string& getVenue() const;
    int getYear() const;
    const std::string& getDOI() const;
    const std::vector<Author>& getAuthors() const;

    // Methods
    void addAuthor(const Author& author);

    // Print Method
    void print() const;
};

#endif
