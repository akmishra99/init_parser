CXX      =  g++
CXXFLAGS = -g 

PROG = ini_file_parser
SOURCE = ini_file_parser.cpp
all:
	$(CXX) $(CXXFLAGS) -o $(PROG) $(SOURCE) 
