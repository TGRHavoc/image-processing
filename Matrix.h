#ifndef MATRIX_H
#define MATRIX_H

/*
    This class is used to store the pixel data for the images being read/manipulated
    The pixel data will be stored in a 2D c-style array.
*/
class Matrix {
public:
	Matrix(int rows, int cols); // Default constructor. Should create the 2D array and populate it with 0s
	~Matrix(); // Destructor. Should destroy the 2D matrix

    void populate(double val); // Should populate the 2D array with the given value

	void operator= (Matrix *m); // Should copy the matrix on the right to the matrix on the left. Requires the two matricies to be the same size.

    void info(); // Should print some info about the current matrix

	void convertArray(double *toConvert); // Should convert a 1D array into a 2D stored in this matrix
    void setAt(int row, int col, double value); // Should set the value at the given ROW,COL index to the value supplied
	double getAt(int row, int col); // Should get the value at the given index

    double getSum(); // Should get the sum of all the elements in the current matrix

    // Get the number of columns this matrix has (width)
	int getCols() {
		return _cols;
	}
    // Get the number of rows this matrix has (height)
	int getRows() {
		return _rows;
	}

private:
	int _rows, _cols; // Our matrix size
	double ** _array; // Our 2D array of pixel values

};

#endif // !MATRIX_H
