#ifndef BIBPARSER_H
#define BIBPARSER_H

#include <string>
#include <vector>
#include "Publication.h"

class BibParser {
public:
    std::vector<Publication> parse(const std::string& filePath, const std::string& instituteAffiliation);
};

#endif // BIBPARSER_H
