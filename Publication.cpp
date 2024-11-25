#include "Publication.h"
#include <iostream>

// Parameterized Constructor
Publication::Publication(const std::string& t, const std::string& v, int y,
                         const std::vector<Author>& a, const std::string& d, 
                         const std::string& aStr)
    : title(t), venue(v), year(y), authors(a), doi(d), authorStr(aStr) {}

// Setters
void Publication::setTitle(const std::string& t) { title = t; }
void Publication::setVenue(const std::string& v) { venue = v; }
void Publication::setYear(int y) { year = y; }
void Publication::setDOI(const std::string& d) { doi = d; }

// Getters
const std::string& Publication::getTitle() const { return title; }
const std::string& Publication::getVenue() const { return venue; }
int Publication::getYear() const { return year; }
const std::string& Publication::getDOI() const { return doi; }
const std::vector<Author>& Publication::getAuthors() const { return authors; }

// Add an author
void Publication::addAuthor(const Author& author) { authors.push_back(author); }

// Print method
void Publication::print() const {
    std::cout << "Title: " << title << "\n"
              << "Venue: " << venue << "\n"
              << "Year: " << year << "\n"
              << "DOI: " << doi << "\n"
              << "Authors: ";
    for (const auto& author : authors) {
        std::cout << author.getName() << "; ";
    }
    std::cout << "\n";
}
