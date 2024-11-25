#include "Author.h"

// Constructor
Author::Author(const std::string& name, const std::string& affiliation)
    : name(name), affiliation(affiliation) {}

// Getter for name
const std::string& Author::getName() const {
    return name;
}

// Getter for affiliation
const std::string& Author::getAffiliation() const {
    return affiliation;
}
