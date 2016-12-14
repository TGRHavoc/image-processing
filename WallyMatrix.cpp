#include <iostream>
#include <ctime>
#include <cmath>

#include "WallyMatrix.h"
#include "Shared.h"

/*
 * Should create a matrix to store the image data in.
 * It should then read the image data from the file, and put said data
 *      into the matrix created.
*/
WallyMatrix::WallyMatrix(int rows, int cols) : Matrix( rows, cols ){
	_filehandler = new FileHandler(_filename); // Initialize the filehandler so we can read the data from the file

	try {
		std::cout << "Reading \"" << _filename << "\"." << std::endl;
		double * data = _filehandler->readFile(getRows(), getCols()); // Read the image data into an array

		convertArray(data); // Put the data into the matrix
	}
	catch (int e) {
		std::cout << "Couldn't create a Wally Matrix." << std::endl;
		std::cout << "Exiting the program" << std::endl;
		throw e;
	}

#ifdef VERBOSE
	std::cout << "Created a wally matrix and populated it from file" << std::endl;
#endif // VERBOSE

}
/*
 * Default destructor.
 * Should delete any dynamically allocated memory that is assigned via this class.
 * Basically, it should just delete the filehandler.
*/
WallyMatrix::~WallyMatrix() {
	delete _filehandler;
	//delete _filename;

#ifdef VERBOSE
	std::cout << "Destroyed wally matrix" << std::endl;
#endif // VERBOSE
}

/*
 * Should calculate the sum of squared differences between the current matrix
 *  and the matrix supplied.
 *
 * @param compareTo The matrix to compare this matrix to
 *
 * @return The similarity score of the matricies using the SSD
*/
double WallyMatrix::sumOfSquaredDifferences(Matrix * compareTo) {
	if (Matrix::getCols() != compareTo->getCols() || Matrix::getRows() != compareTo->getRows()) { // If they're not the same size.
		std::cout << "Cannot do SSD.. The matricies provided aren't the same size" << std::endl;
		throw 1;
	}

#ifdef VERBOSE
	std::cout << "Getting SSD" << std::endl;
#endif
	std::clock_t start = std::clock();

    double ssd = 0;

	for (int y = 0; y < Matrix::getRows(); y++) {
		for (int x = 0; x < Matrix::getCols(); x++) {

            if (Matrix::getAt(y, x) != 255){// Skip all white pixels (only compare the actual Wally image)

                double diff = (Matrix::getAt(y, x)) - (compareTo->getAt(y, x)); // Get the difference between the two pixel values

    			ssd += diff*diff; // Square them, and add them to the ssd score
            }else{
                #ifdef VERBOSE
                std::cout << "Skipping" << std::endl;
                #endif
            }
		}
	}

	std::clock_t end = std::clock();
#ifdef VERBOSE
	std::cout << "SSD took " << (double(end - start) / CLOCKS_PER_SEC) << " seconds" << std::endl;
#endif

    return ssd;
}
/*
 * Should calculate the similarity score of the matricies using the Normalized Correlation
 *  algorithm.
 *
 * @param compareTo The matrix to compare this one to
 *
 * @return The similarity score of the two matrices using the NC algorithm
*/
double WallyMatrix::normalizedCorrelation(Matrix * compareTo) // This is actually called Normalized Correlation in the lecture slides
{
    std::clock_t start = std::clock();

    double imgMean = (1 / Matrix::getRows()*Matrix::getCols()) * Matrix::getSum();// Get the mean of the current image
    double tplMean = (1 / compareTo->getRows() * compareTo->getCols()) * compareTo->getSum(); // Get the mean of the template image

    // Create twom matrices to hold the data in
    Matrix myMat(Matrix::getRows(), Matrix::getCols());
    Matrix oMat(compareTo->getRows(), compareTo->getCols());

    // Copy the original data into the temporary matrices
    myMat = this;
    oMat = compareTo;

    for (int i = 0; i < Matrix::getRows(); i++) {
        for (int j = 0; j < Matrix::getCols(); j++) {
            // Remove the mean of the image from all the pixel values
            myMat.setAt(i, j, myMat.getAt(i, j) - imgMean);
            oMat.setAt(i, j, oMat.getAt(i, j) - tplMean);
        }
    }

    double sumOfDot = 0;
    // No need to skip white pixels... This algo doesn't give a crap
    for(int y = 0; y < myMat.getRows(); y++){
        for(int x = 0; x < myMat.getCols(); x++){

            double dotProduct = oMat.getAt(y, x) * myMat.getAt(y, x); // Get the dot product of the pixel values from the temp matrices

            sumOfDot += dotProduct; // Add it to the sum
        }
    }

    double sumOfTplSq = oMat.getSum() * oMat.getSum(); // Calculate the dot product of the sum of the template image
    double sumOfImgSq = myMat.getSum() * myMat.getSum();// Calculate the dot product of the sum of the main image

    double sqrtOf = std::sqrt(sumOfTplSq * sumOfImgSq); // Find the square root of the dot product of the sum of the images

    std::clock_t end = std::clock();

#ifdef VERBOSE
	std::cout << "Coeff Normed took " << (double(end - start) / CLOCKS_PER_SEC) << " seconds" << std::endl;
#endif

    return sumOfDot / sqrtOf; // Divide the sum of the dot products (from the images) by the square root calculated above.
}
