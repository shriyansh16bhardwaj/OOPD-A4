CXX = g++
CXXFLAGS = -Wall -std=c++17

OBJECTS = main.o Author.o Publication.o BibParser.o PublicationManager.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

main.o: main.cpp Author.h Publication.h BibParser.h PublicationManager.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Author.o: Author.cpp Author.h
	$(CXX) $(CXXFLAGS) -c Author.cpp

Publication.o: Publication.cpp Publication.h Author.h
	$(CXX) $(CXXFLAGS) -c Publication.cpp

BibParser.o: BibParser.cpp BibParser.h Publication.h Author.h
	$(CXX) $(CXXFLAGS) -c BibParser.cpp

PublicationManager.o: PublicationManager.cpp PublicationManager.h Publication.h Author.h
	$(CXX) $(CXXFLAGS) -c PublicationManager.cpp

clean:
	rm -f $(OBJECTS) $(TARGET)