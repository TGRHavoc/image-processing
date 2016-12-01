#include <iostream>

#include "Matrix.h"
#include "Shared.h"

Matrix::Matrix(int rows, int cols){
	_array = new double*[rows];
	for (int i = 0; i < rows; i++) {
		_array[i] = new double[cols];
	}

#ifdef VERBOSE
	std::cout << "Created a matrix " << rows << " by " << cols << std::endl;
#endif

	_rows = rows;
	_cols = cols;
	populate(0.0);
}


Matrix::~Matrix(){
	for (int i = 0; i < Matrix::getRows(); i++) {
		delete[] _array[i];
	}

	delete[] _array;
#ifdef VERBOSE
	std::cout << "Destroyed matrix" << std::endl;
#endif // VERBOSE
}

void Matrix::populate(double val){
	for (int i = 0; i < Matrix::getRows(); i++) {
		for (int j = 0; j < Matrix::getCols(); j++) {
			_array[i][j] = val;
		}
	}

#ifdef VERBOSE
	std::cout << "Populated matrix with the value " << val << std::endl;
#endif
}

double Matrix::getAt(int row, int col){
	if (row > Matrix::getRows() || row < 0 || col > Matrix::getCols() || col < 0) {
		std::cout << "The values supplied are out of bounds for this matrix ("<< row << ":" << Matrix::getRows() << " , " << col << ":" << Matrix::getCols() << ")" << std::endl;
		return double(); // Just return a default value..
	}

	//std::cout << "Returning " << _array[row][col] << std::endl;
	return _array[row][col];
}

void Matrix::info(){

	for (int i = 0; i < Matrix::getRows(); i++) {
		for (int j = 0; j < Matrix::getCols(); j++) {
			std::cout << _array[i][j] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << "This matrix has " << Matrix::getRows() * Matrix::getCols() << " elements. (" << Matrix::getRows() << "x" << Matrix::getCols() << ")" << std::endl;
}

void Matrix::convertArray(double * toConvert){
	for (int i = 0; i < Matrix::getRows(); i++) {
		for (int j = 0; j < Matrix::getCols(); j++) {
			_array[i][j] = toConvert[ i * Matrix::getCols() + j ];
		}
	}

	delete[] toConvert; // Delete the array, the data lives inside us now
}

void Matrix::setAt(int row, int col, double value, bool show){
    if (row > Matrix::getRows() || row < 0 || col > Matrix::getCols() || col < 0) {
        std::cout << "The values supplied are out of bounds for this matrix ("<< row << ":" << Matrix::getRows() << " , " << col << ":" << Matrix::getCols() << ")" << std::endl;
		return; // Just return a default value..
	}
    if (show)
        std::cout << "Setting " << row << "," << col << " to " << value << std::endl;
    _array[row][col] = value;
}

double Matrix::getSum(){
#ifdef VERBOSE
	std::cout << "Getting sum" << std::endl;
#endif

    double sum = 0;

    for(int i = 0; i < Matrix::getRows(); i++){
        for(int j = 0; j < Matrix::getCols(); j++){
            sum += Matrix::getAt(i, j);
        }
    }
    return sum;
}

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
