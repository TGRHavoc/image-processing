#include <iostream>

#include "SceneMatrix.h"
#include "Shared.h"

/*
 * Should create a matrix to store the image data in.
 * It should then read the image data from the file, and put said data
 *      into the matrix created.
 *
*/
SceneMatrix::SceneMatrix(int rows, int cols) : Matrix(rows, cols) {

	_filehandler = new FileHandler(_filename);// Initialize the filehandler with the file so that we can read it

	try {
		std::cout << "Reading \"" << _filename << "\"." << std::endl;
		double * data = _filehandler->readFile(getRows(), getCols()); // Read the data, and put it into an array

		convertArray(data);// Copy the data from the array into the matrix
	}
	catch (int e) { // readFile can throw an error (file couldn't be opened)
		std::cout << "Couldn't create a Scene Matrix." << std::endl;
		std::cout << "Exiting the program" << std::endl;
		exit(e); // Well.. We couldn't get the large image data so, might as well give up
	}

#ifdef VERBOSE
	std::cout << "Created a scene matrix and populated it from file" << std::endl;
#endif // VERBOSE

}

/*
 * Default destructor.
 * Should delete any dynamically allocated memory that is assigned via this class.
 * Basically, it should just delete the filehandler.
*/
SceneMatrix::~SceneMatrix() {
	delete _filehandler;
	//delete _filename;

#ifdef VERBOSE
	std::cout << "Destroyed scene matrix" << std::endl;
#endif // VERBOSE
}
/*
 * Should get a smaller image that appears at the given coordinates.
 * If the coordinates given try to get an image that appears off-sceen then the
 *  returned matrix will be smaller than expected.
 * Otherwise, the matrix returned will be the same size as the matrix supplied in
 *  arguments
 *
 * @param x The x coordiinate of where the smaller image begins inside the large image
 * @param y The y coordinate of where the smaller image begins inside the large image
 * @param smallerImage The size of the image that this method should return
 *
 * @return A matrix that represents an image that begins at the given coordinates inside the large image
*/
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
		xEnd = Matrix::getCols(); // End at the end of the large image
	}
	if (yEnd > Matrix::getRows()) {
		yEnd = Matrix::getRows(); // End at the end of the large image
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
            returnMatrix->setAt(_y, _x, value); // Populate the sub image with the data we get from the large image

            _x++;
        }
        _y++;
    }

    return returnMatrix;
}
/*
 * Should modify the current matrix to put a black box (0's) around the given smaller image
 *
 * @param x The x coordinate of where the smaller image begins inside the large image
 * @param y The y coordinate of where the smaller image begins inside the large image
 * @param size The size of the image that this method should put a box around
*/
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

    // Put a box around he smaller image
    for(int a = 0; a <= 1; a++){ // Do it a amount of times (make it thick)
        for(int i = yStart; i < yEnd; i++){ // Loop through all the data of the smaller image
            for(int j = xStart; j < xEnd; j++){

                if ( i == yStart || i == yEnd-1 || j == xStart || j == xEnd-1){ // If we're at the top, left, right or bottom of where the box is...
                    Matrix::setAt(i , j, 0); // Draw it (set the pixels to 0)
                }

            }
        }

        // Make the box one pixel bigger (makes it thicker)
        yStart++;
        xStart++;
        yEnd++;
        xEnd++;
    }

}
