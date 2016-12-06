#ifndef WALLYMATRIX_H
#define WALLYMATRIX_H

#include "Matrix.h"
#include "FileHandler.h"

/*
    This class is used to store the pixel data for the template image that is
        used for comparison (Wally). It's a child of the matrix class
*/
class WallyMatrix : public Matrix {
public:
	WallyMatrix(int rows, int cols); // Default constructor
	~WallyMatrix(); // Default destructor

	double sumOfSquaredDifferences(Matrix * compareTo); // Should calculate the Sum of Squared Differences between this matrix and the supplied matrix
	double normalizedCorrelation(Matrix * compareTo); // Should calculate the Normalized Correlation between this matrix and the supplied matrix
private:
	FileHandler * _filehandler; // The filehandler for Wally_grey.txt

	char * _filename = "Wally_grey.txt";
};

#endif // !WALLYMATRIX_H
