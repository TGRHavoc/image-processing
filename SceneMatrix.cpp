#include <iostream>

#include "SceneMatrix.h"
#include "Shared.h"

SceneMatrix::SceneMatrix(int rows, int cols) : Matrix(rows, cols) {

	_filehandler = new FileHandler(_filename);

	try {
		std::cout << "Reading \"" << _filename << "\"." << std::endl;
		double * data = _filehandler->readFile(getRows(), getCols());

		convertArray(data);// Convert array deleted the data array when it's copied
	}
	catch (int e) {
		std::cout << "Couldn't create a Scene Matrix." << std::endl;
		std::cout << "Exiting the program" << std::endl;
		exit(e);
	}

#ifdef VERBOSE
	std::cout << "Created a scene matrix and populated it from file" << std::endl;
#endif // VERBOSE

}


SceneMatrix::~SceneMatrix() {
	delete _filehandler;
	//delete _filename;

#ifdef VERBOSE
	std::cout << "Destroyed scene matrix" << std::endl;
#endif // VERBOSE
}

Matrix * SceneMatrix::getSmallerImage(int x, int y, Matrix * smallerImage){
    Matrix * returnMatrix = new Matrix( smallerImage->getRows(), smallerImage->getCols() );

    // Where we start in the large image
	int xStart = x; // *smallerImage->getCols();
	int yStart = y; // *smallerImage->getRows();

#ifdef VERBOSE
	std::cout << "xStart = " << xStart << "\tyStart = " << yStart << std::endl;
#endif

    //Where we end in the large image
    int xEnd = xStart + smallerImage->getCols();
    int yEnd = yStart + smallerImage->getRows();

	if (xEnd > Matrix::getCols()) {
		xEnd = Matrix::getCols();
	}
	if (yEnd > Matrix::getRows()) {
		yEnd = Matrix::getRows();
	}

#ifdef VERBOSE
	std::cout << "xEnd = " << xEnd << ", yEnd = " << yEnd << std::endl;
#endif

    //Where we put the data into the new image
    int _x = 0;
    int _y = 0;

    for (int _row = yStart; _row < yEnd; _row++){
        _x = 0;
        for(int _col = xStart; _col < xEnd; _col++){

            double value = Matrix::getAt(_row, _col); // The value to put into the new image
            returnMatrix->setAt(_y, _x, value);

            _x++;
        }
        _y++;
    }

    return returnMatrix;
}

void SceneMatrix::debugSmallerImage(int x, int y, Matrix * size){
    // Where we start in the large image
	int xStart = x; // smallerImage->getCols();
	int yStart = y; // smallerImage->getRows();

    //Where we end in the large image
    int xEnd = xStart + size->getCols();
    int yEnd = yStart + size->getRows();

	if (xEnd > Matrix::getCols()) {
		xEnd = Matrix::getCols();
	}
	if (yEnd > Matrix::getRows()) {
		yEnd = Matrix::getRows();
	}

    for(int a = 0; a <= 1; a++){
        for(int i = yStart; i < yEnd; i++){
            for(int j = xStart; j < xEnd; j++){

                if ( i == yStart || i == yEnd-1 || j == xStart || j == xEnd-1){
                    Matrix::setAt(i , j, 0);
                }

            }
        }

        yStart++;
        xStart++;
        yEnd++;
        xEnd++;
    }

}
