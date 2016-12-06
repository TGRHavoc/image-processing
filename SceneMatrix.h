#ifndef SCENEMATRIX_H
#define SCENEMATRIX_H

#include "Matrix.h"
#include "FileHandler.h"

/*
    This class is used to store the pixel data for the large image that is
        used for comparison (Scene). It's a child of the matrix class
*/
class SceneMatrix : public Matrix {
public:
	SceneMatrix(int rows, int cols); // Default constructor for the class
	~SceneMatrix(); // Default destructor

    Matrix * getSmallerImage(int x, int y, Matrix * smallerImage); // Should get a smaller matrix (of size smallerImage) starting at the given index (x+y)
    void debugSmallerImage(int x, int y, Matrix * size); // Should put a black square around the smaller image that starts at the coords given

private:
	FileHandler * _filehandler; // The filehandler for Cluttered_scene.txt

	char * _filename = "Cluttered_scene.txt";
};

#endif // !SCENEMATRIX_H
