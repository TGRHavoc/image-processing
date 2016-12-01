#include <iostream>
#include <fstream>
#include <istream>

#include "FileHandler.h"
#include "Shared.h"

/*
 *   Default constructor. Used to create a FileHandler for writing only.
*/
FileHandler::FileHandler(){

#ifdef VERBOSE
	std::cout << "You have created a filehandler without a in file.. You cannot use the read functions" << std::endl;
#endif

    FileHandler::filename = NULL;
}
/*
 *  Created a filehandler to read and write to a file.
 *  @param filename a pointer to a character array for the filename
*/
FileHandler::FileHandler(char *filename)
{
	FileHandler::filename = filename;
}
/*
 *  Destructor. This doesn't have to do anything as I'm not assigning memory
 *      or anything like that in the constructor.
*/
FileHandler::~FileHandler()
{
#ifdef VERBOSE
	if (!FileHandler::filename){
		std::cout << "A filehandler for a file without a name has been destroyed" << std::endl;
		return;
	}
	std::cout << "File handler for \"" << FileHandler::filename << "\" has been destroyed" << std::endl;
#endif
}
/*
 *  Reads image data from the file and returns a pointer to a array
 *      that contains the file's data.
 *  @param rows The number of rows in the image (height in pixels)
 *  @param cols The number of columns in the image (width in pixels)
 *  @return A array that contains the pixel data for the inage
*/
double * FileHandler::readFile(int rows, int cols)
{
    if( FileHandler::filename == false ){ // If it's a write-only filehandler
        std::cout << "I don't have a file to read.. " << std::endl;
        throw 1; // Just throw an error... Break everything!!
    }

	double * data = new double[cols*rows]; // Array of data we've read in
	int i = 0;

	std::ifstream _file(FileHandler::filename); // Open this file for reading

	if (_file.is_open()) { // Make sure it's open
		while (_file.good()) { // While there's no erors
			if (i > ((rows * cols) - 1)) break; // If we're at the end of the image data

			_file >> *(data + i); // Read the current pixel value into the array
#ifdef VERBOSE
			std::cout << (char)*(data + i);
#endif
			i++;
		}

        std::cout << "I've read all the data from \"" << FileHandler::filename << "\".\n";

		_file.close(); // Make sure the file is closed
	}
	else { // We couldn't open the file :(
		std::cerr << "Couldn't open file with the name \"" << FileHandler::filename << "\".\nPlease make sure it's in the same directory as the program." << std::endl;
		throw 1;
	}

	return data; // Return the array of data
}
/*
 *  Reads the image data from the file and turns it into a Matrix.
 *  @param rows The number of rows in the image (height in pixels)
 *  @param cols The number of columns in the image (width in pixels)
 *  @return A matrix containing the pixel values for the image
*/
Matrix * FileHandler::readImage(int rows, int cols) {

	Matrix * matrix = new Matrix(rows, cols); // Our image matrix
	int i = 0;
	try {
		double * data = readFile(rows, cols); // Get the array of pixel values

#ifdef VERBOSE
		std::cout << "\nData before convertion: " << *data << std::endl;
#endif

		matrix->convertArray(data); // Put the pixel data into the matrix
		//Data should be deleted when the convertArray function has finished.

		return matrix;
	}
	catch (int e) { // Make sure we catch any errors (file not opening etc)
		throw e;
	}
}
/*
 *  Writes a given matrix to the file supplied in PGM format.
 *  @param outputfile A pointer to a character array for the output filename.
 *  @param matrix A pointer to the Matrix to write
 *  @param Q What type of image is it (255=Greyscale, 0=Binary)
*/
void FileHandler::writeMatrix(char * outputFile, Matrix * matrix, int Q) {
	int rows = matrix->getRows(); // How heigh is the image
	int cols = matrix->getCols(); // How wide is the image
	unsigned char * imageData = (unsigned char *) new unsigned char[rows * cols];

    //Convert the matrix to a array
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			imageData[i * cols + j] = (unsigned char)matrix->getAt(i, j);
		}
	}

	std::ofstream _file;
    // Open the file for writing, in binary, overriding any existing file.
	_file.open(outputFile, std::ios::out | std::ios::binary | std::ios::trunc);

	if (!_file) {
		std::cout << "Cann't open file \"" << outputFile << "\" for writing." << std::endl;
		throw 1;
	}

#ifdef VERBOSE
	std::cout << "Writing headers" << std::endl;
#endif
    // Magical header for PGM files.
	_file << "P5" << std::endl;
	_file << cols << " " << rows << std::endl;
	_file << Q << std::endl;

    // Write the image data
	_file.write(reinterpret_cast<char *>(imageData), (rows*cols) * sizeof(unsigned char));

#ifdef VERBOSE
	std::cout << "Written image data." << std::endl;
#endif

	if (_file.fail()) {// If we didn't write :(
		std::cout << "Couldn't write image data to file \"" << outputFile << "\"\n";
		throw 1;
	}

	_file.close(); // Close that file!
	delete[] imageData; // Delete the imageData.. It's been saved anyways
}
