#include <iostream>
#include <ctime>
#include <cmath>

#include "WallyMatrix.h"
#include "Shared.h"

WallyMatrix::WallyMatrix(int rows, int cols) : Matrix( rows, cols ){
	_filehandler = new FileHandler(_filename);

	try {
		std::cout << "Reading \"" << _filename << "\"." << std::endl;
		double * data = _filehandler->readFile(getRows(), getCols());

		convertArray(data); // convertArray deleted the data array when it's finished
	}
	catch (int e) {
		std::cout << "Couldn't create a Wally Matrix." << std::endl;
		std::cout << "Exiting the program" << std::endl;
		exit(e);
	}

#ifdef VERBOSE
	std::cout << "Created a wally matrix and populated it from file" << std::endl;
#endif // VERBOSE

}


WallyMatrix::~WallyMatrix() {
	delete _filehandler;
	//delete _filename;

#ifdef VERBOSE
	std::cout << "Destroyed wally matrix" << std::endl;
#endif // VERBOSE
}


double WallyMatrix::sumOfSquaredDifferences(Matrix * compareTo) {
	if (Matrix::getCols() != compareTo->getCols() || Matrix::getRows() != compareTo->getRows()) {
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

                double diff = (Matrix::getAt(y, x)) - (compareTo->getAt(y, x));

    			ssd += diff*diff;
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

double WallyMatrix::normalizedCorrelation(Matrix * compareTo) {
	if (Matrix::getCols() != compareTo->getCols() || Matrix::getRows() != compareTo->getRows()) {
		std::cout << "Cannot do NC.. The matricies provided aren't the same size" << std::endl;
		throw 1;
	}
	std::clock_t start = std::clock();

    double dotProduct = 0;
    double mySqured = 0;
    double tSquared = 0;

    for(int y = 0; y < Matrix::getRows(); y++){
        for(int x = 0; x < Matrix::getCols(); x++){
            if (Matrix::getAt(y, x) != 255){

                dotProduct += compareTo->getAt(y, x) * Matrix::getAt(y, x);

                mySqured += Matrix::getAt(y, x) * Matrix::getAt(y, x);
                tSquared += compareTo->getAt(y, x) * compareTo->getAt(y, x);
            }
        }
    }

    double squredroot = std::sqrt(tSquared * mySqured);

#ifdef VERBOSE
	std::cout << "NC: " << dotProduct / squredroot << std::endl;
#endif
	std::clock_t end = std::clock();

#ifdef VERBOSE
	std::cout << "NC took " << (double(end - start) / CLOCKS_PER_SEC) << " seconds" << std::endl;
#endif

	return dotProduct / squredroot;
}

double WallyMatrix::coefficientNormed(Matrix * compareTo) // This is actually called Normalized Correlation in the lecture slides
{
    std::clock_t start = std::clock();

    double imgMean = (1 / Matrix::getRows()*Matrix::getCols()) * Matrix::getSum();
    double tplMean = (1 / compareTo->getRows() * compareTo->getCols()) * compareTo->getSum();

    Matrix myMat(Matrix::getRows(), Matrix::getCols());
    Matrix oMat(compareTo->getRows(), compareTo->getCols());

    myMat = this;
    oMat = compareTo;

    for (int i = 0; i < Matrix::getRows(); i++) {
        for (int j = 0; j < Matrix::getCols(); j++) {
            myMat.setAt(i, j, myMat.getAt(i, j) - imgMean);
            oMat.setAt(i, j, oMat.getAt(i, j) - tplMean);
        }
    }

    double sumOfDot = 0;
    // No need to skip white pixels... This algo doesn't give a crap
    for(int y = 0; y < myMat.getRows(); y++){
        for(int x = 0; x < myMat.getCols(); x++){
            double dotProduct = oMat.getAt(y, x) * myMat.getAt(y, x);
            sumOfDot += dotProduct;
        }
    }

    double sumOfTplSq = oMat.getSum() * oMat.getSum();
    double sumOfImgSq = myMat.getSum() * myMat.getSum();

    double sqrtOf = std::sqrt(sumOfTplSq * sumOfImgSq);

    std::clock_t end = std::clock();

#ifdef VERBOSE
	std::cout << "Coeff Normed took " << (double(end - start) / CLOCKS_PER_SEC) << " seconds" << std::endl;
#endif

    return sumOfDot / sqrtOf;
}
