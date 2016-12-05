#ifndef SCENEMATRIX_H
#define SCENEMATRIX_H

#include "Matrix.h"
#include "FileHandler.h"

class SceneMatrix : public Matrix {
public:
	SceneMatrix(int rows, int cols);
	~SceneMatrix();

    Matrix * getSmallerImage(int x, int y, Matrix * smallerImage); // Should get a smaller matrix (of size smallerImage) starting at the given index (x+y)
    void debugSmallerImage(int x, int y, Matrix * size);
    
private:
	FileHandler * _filehandler;

	char * _filename = "Cluttered_scene.txt";
};

#endif // !SCENEMATRIX_H
