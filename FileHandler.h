#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "Matrix.h"

class FileHandler {
public:
    FileHandler();
	FileHandler(char *filename);
	~FileHandler();

	double* readFile(int rows, int cols);

    //Let's return a pointer to this image matrix. (It might be too large for stack)
     Matrix * readImage(int rows, int cols);

    //Writes a matrix to a pgm file
    void writeMatrix(char * outputFile, Matrix * matrix, int Q = 255);

private:
	char *filename;
};

#endif // !FILEHANDLER_H
