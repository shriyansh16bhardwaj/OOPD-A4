# OOPD Assignment 4

This assignment implements a system for managing and parsing publication records in the BibTeX format. It uses C++ to parse `.bib` files and map the data to structured `Publication` objects. The system is capable of storing publication details, searching for publications by author, and calculating the average number of co-authors for a specific author.

## Features
- **Parse BibTeX files**: Read and parse publications from `.bib` files.
- **Author and Affiliation Validation**: Ensure authors are affiliated with a specific institution (e.g., "IIIT-Delhi").
- **Search by Author**: Find all publications by a specific author.
- **Average Co-Authors Calculation**: Calculate the average number of co-authors for a given author.
- **Publication Management**: Store and manage publications with details like title, venue, year, authors, and DOI.

## Classes
### `Publication`
The `Publication` class holds information about a publication, such as its title, venue, authors, year, and DOI.

#### Constructor:
- `Publication(std::string title, std::string venue, std::vector<Author> authors, int year, std::string doi)`

#### Methods:
- `void addAuthor(const Author& author)`: Adds an author to the publication.
- `std::string getTitle() const`: Returns the title of the publication.
- `std::string getVenue() const`: Returns the venue of the publication.
- `std::vector<Author> getAuthors() const`: Returns the list of authors of the publication.
- `int getYear() const`: Returns the publication year.
- `std::string getDOI() const`: Returns the DOI of the publication.

### `Author`
The `Author` class holds the name and affiliation of an author.

#### Constructor:
- `Author(std::string name, std::string affiliation = "")`: Initializes an author with the name and optional affiliation.

#### Methods:
- `std::string getName() const`: Returns the name of the author.
- `std::string getAffiliation() const`: Returns the affiliation of the author.
- `bool operator==(const Author& other) const`: Compares two authors for equality.

### `PublicationManager`
The `PublicationManager` class manages a collection of `Publication` objects. It provides methods for adding publications, searching by author, and calculating the average number of co-authors.

#### Methods:
- `void addPublication(const Publication& publication)`: Adds a publication to the manager.
- `std::vector<Publication> findPublicationsByAuthor(const std::string& authorName) const`: Finds all publications by a specific author.
- `double calculateAverageCoAuthors(const std::string& authorName) const`: Calculates the average number of co-authors for a given author.

### `BibParser`
The `BibParser` class is responsible for parsing `.bib` files and extracting relevant publication data. It maps the parsed data into `Publication` objects.

#### Methods:
- `std::vector<Publication> parse(const std::string& filePath, const std::string& instituteAffiliation)`: Parses the `.bib` file and returns a vector of `Publication` objects.

## Usage

1. **Include Header Files**: Include the necessary header files in your program:

```cpp
#include "PublicationManager.h"
#include "Publication.h"
#include "Author.h"
#include "BibParser.h"

2. Parsing a .bib file: To parse a .bib file, use the BibParser::parse method. The function requires the file path of the .bib file and the institute affiliation to ensure at least one author is affiliated with the given institution.

std::vector<Publication> publications = BibParser::parse("path/to/your/file.bib", "IIIT-Delhi");

3. Adding Publications: Once parsed, publications can be added to the PublicationManager:
PublicationManager manager;
for (const auto& pub : publications) {
    manager.addPublication(pub);
}

4. Searching for Publications by Author: To find all publications by a specific author, use the findPublicationsByAuthor method:

std::vector<Publication> authorPublications = manager.findPublicationsByAuthor("Arani Bhattacharya");

5. Calculating Average Co-Authors: To calculate the average number of co-authors for a specific author:

double avgCoAuthors = manager.calculateAverageCoAuthors("Arani Bhattacharya");

6. Compilation
To compile the program, make sure to link all the required .cpp files. You can use a Makefile or manually compile the program using g++:

make 
./main

7. Acknowledgements
The BibTeX parsing logic was adapted for this project to handle basic parsing of .bib files.
Thanks to contributors and developers of C++ libraries.
Thanks to Chatgpt which helped in fixing errors.

## Author
Shriyansh Bhardwaj