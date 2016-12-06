#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "Matrix.h"

class FileHandler {
public:
    // Default constructor, used to only write data to a file
    FileHandler();
    // constructor used to read data in from a file
	FileHandler(char *filename);
    // Default destructor
	~FileHandler();

    // Reads the data in from a text file that represents an image
	double* readFile(int rows, int cols);

    // Same as the above method but, returns a matrix
     Matrix * readImage(int rows, int cols);

    //Writes a matrix to a pgm file
    void writeMatrix(char * outputFile, Matrix * matrix, int Q = 255);

private:
    // The file (if any) we can read data from
	char *filename;
};

#endif // !FILEHANDLER_H
