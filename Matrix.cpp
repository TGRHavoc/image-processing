#include <iostream>

#include "Matrix.h"
#include "Shared.h"

/*
 * Default constructor for a Matrix.. THis should create a 2D c-style array and populate it with 0's
*/
Matrix::Matrix(int rows, int cols){
    _array = new double*[rows]; // An array for our rows that contains our columns
	for (int i = 0; i < rows; i++) {
		_array[i] = new double[cols]; // An array for our columns that contain our pixel data
	}

#ifdef VERBOSE
	std::cout << "Created a matrix " << rows << " by " << cols << std::endl;
#endif
    // Set our private properties to the values we've used to create the array
	_rows = rows;
	_cols = cols;
    // Set all pixel values to 0. We'll override them later
	populate(0.0);
}

/*
 * Default destructor for the Matrix class.
 * This should perform a "deep delete" to make sure all memory is freed
*/
Matrix::~Matrix(){
	for (int i = 0; i < Matrix::getRows(); i++) {
		delete[] _array[i]; // Delete our columns with their data
	}

	delete[] _array; // Delete our rows
#ifdef VERBOSE
	std::cout << "Destroyed matrix" << std::endl;
#endif // VERBOSE
}

/*
 * Populates the 2D array with the values supplied.
 * @param val The value to populate the array with
*/
void Matrix::populate(double val){
	for (int i = 0; i < Matrix::getRows(); i++) { // For each row
		for (int j = 0; j < Matrix::getCols(); j++) { // For each column
			_array[i][j] = val; // Set the value to what was supplied
		}
	}

#ifdef VERBOSE
	std::cout << "Populated matrix with the value " << val << std::endl;
#endif
}
/*
 * Gets the data that is stored in the 2D array at the position supplied.
 * Note: Must supply row (y) first, then the column (x)
 * @param row The row the pixel is on
 * @param col The column the pixel is on
 * @return The value of the element at the given index
*/
double Matrix::getAt(int row, int col){
	if (row > Matrix::getRows() || row < 0 || col > Matrix::getCols() || col < 0) { /// Are the values out of bounds??
		std::cout << "The values supplied are out of bounds for this matrix ("<< row << ":" << Matrix::getRows() << " , " << col << ":" << Matrix::getCols() << ")" << std::endl;
		return double(); // Just return a default value..
	}

	//std::cout << "Returning " << _array[row][col] << std::endl;
	return _array[row][col]; // Return it!
}

/*
 * Should print the matrix to std::out along with the size of the matrix
 *  and how many elements it contains
*/
void Matrix::info(){

	for (int i = 0; i < Matrix::getRows(); i++) {
		for (int j = 0; j < Matrix::getCols(); j++) {
			std::cout << _array[i][j] << " "; // Print each column on the same line, seperated by a space
		}
		std::cout << std::endl; //When reach a new row, start it on a new line
	}

	std::cout << "This matrix has " << Matrix::getRows() * Matrix::getCols() << " elements. (" << Matrix::getRows() << "x" << Matrix::getCols() << ")" << std::endl;
}
/*
 * Should convert a 1D array to the current matrix.
 * @param toConvert A pointer to a double array to copy the data from
*/
void Matrix::convertArray(double * toConvert){
	for (int i = 0; i < Matrix::getRows(); i++) {
		for (int j = 0; j < Matrix::getCols(); j++) {
			_array[i][j] = toConvert[ i * Matrix::getCols() + j ]; // Put the 1D data into the 2D array, at the correct position
		}
	}

	delete[] toConvert; // Delete the array, the data lives inside us now
}
/*
 * Sets the value at the given index to the value supplied.
 * @param row The row of the value you want to change
 * @param col The column of the value you want to change
 * @param value The value you want to change it to
*/
void Matrix::setAt(int row, int col, double value){
    if (row > Matrix::getRows() || row < 0 || col > Matrix::getCols() || col < 0) {// If it's out of bounds
        std::cout << "The values supplied are out of bounds for this matrix ("<< row << ":" << Matrix::getRows() << " , " << col << ":" << Matrix::getCols() << ")" << std::endl;
		return; // Just return.. I can't do anything about it being out of bounds
	}

    _array[row][col] = value; //Set the value!
}

/*
 * Gets the sum of all the elements inside the Matrix
 * @return The sum of all the elements in the matrix
*/
double Matrix::getSum(){
    double sum = 0;

    for(int i = 0; i < Matrix::getRows(); i++){
        for(int j = 0; j < Matrix::getCols(); j++){
            sum += Matrix::getAt(i, j); // Add the current value onto the sum
        }
    }
    return sum;
}
/*
 * This should copy the data from the matrix on the right of the operator to the matrix on the left
 * for example: matrix1 = matrix2
 *      Will copy all the data from "matrix2" into "matrix1";
 *
 * Note: This performs a deep copy.
*/
void Matrix::operator=(Matrix * m) {
	int rows = m->getRows();
	int cols = m->getCols();

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			Matrix::setAt(i, j, m->getAt(i, j));
		}
	}
#ifdef VERBOSE
	std::cout << "Copied matrix from operator" << std::endl;
#endif
}
