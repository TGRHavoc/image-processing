#ifndef WALLYMATRIX_H
#define WALLYMATRIX_H

#include "Matrix.h"
#include "FileHandler.h"

class WallyMatrix : public Matrix {
public:
	WallyMatrix(int rows, int cols);
	~WallyMatrix();

	double sumOfSquaredDifferences(Matrix * compareTo); // Should calculate the Sum of Squared Differences between this matrix and the supplied matrix
	double normalizedCorrelation(Matrix * compareTo); // Should calculate the Normalized Correlation between this matrix and the supplied matrix
    
    // The best image processing algorithm for this job
    double coefficientNormed(Matrix * compareTo);

private:
	FileHandler * _filehandler;

	char * _filename = "Wally_grey.txt";
};

#endif // !WALLYMATRIX_H
