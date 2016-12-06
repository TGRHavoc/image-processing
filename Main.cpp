// System Includes
#include <iostream> // For outputting text to terminal
#include <vector> // For storing NC scores in a nice list
#include <algorithm> // For sorting the NC scores

#include <string> // For creating dynamic file names (e.g. nc_1.pgm)
#include <cstring> // To make the program compile with g++

#include "FileHandler.h" // Allows me to save the image data to file
#include "Shared.h" // For VERBOSE

#include <ctime>

// I need to show inheritance, so I did it on the Matrix class... I couldn't think of any other classes to do it to
// They're not nessercery for the program but, needed for the assignment
#include "WallyMatrix.h" // The wally image matrix
#include "SceneMatrix.h" // The scene image matrix

// The image dimensions for the Wally Image
#define WALLY_ROWS 49 // How high is it?
#define WALLY_COLS 36 // How wide is it?

// The image dimensions for the cluttered scene
#define SCENE_ROWS 768 // How high is it?
#define SCENE_COLS 1024 // How wid

// Structure to group the local image co-ords with their NC score
struct NNSScore {
	int x;
	int y;
    bool isSsd; // Set to true if using the SSD algo to compare images

	double score; // The NC score
	bool operator< (NNSScore &imgs) {
        if (isSsd)
            return score < imgs.score;

		return score > imgs.score; // The closer to 1, the better
	}
};


int main(int argc, char** argv)
{
    // Start getting the user input on how the program should work
	int top = 0;
	bool doHalfs = false;

    std::cout << "Would you like me to generate a list of best matches?\nIf so, please enter the number of best matches you want me to generate. If not, just enter 0.\n";
    std::cin >> top;

    int mode = 0;
    std::cout << "How would you like me to search the image?\n1. Pixel by pixel (slowest, most likely to find the template image)" << std::endl;
    std::cout << "2. In steps of " << WALLY_COLS/2 << "x" << WALLY_ROWS/2 << " (faster, less likely to find the template image) - Suggested" << std::endl;
    std::cout << "3. In steps of " << WALLY_COLS << "x" << WALLY_ROWS << " (fastest, least likely to find the template image)" << std::endl;

    std::cin >> mode;
    if (mode <= 0 || mode > 3){
        std::cout << "Sorry, I don't know what option " << mode << " is. I'm going to default to 1." << std::endl;
        mode = 1;
    }
    // end of getting user input

	WallyMatrix * wallyMatrix = new WallyMatrix(WALLY_ROWS, WALLY_COLS); // Creates the Wally matrix from the "Wally_grey.txt" file
	SceneMatrix * clutteredMatrix = new SceneMatrix(SCENE_ROWS, SCENE_COLS); // Creates the scene matrix from the "Cluttered_scene.txt" file

	int imageW = clutteredMatrix->getCols(); // How big is the scene image? Used in the for loops below
    int imageH = clutteredMatrix->getRows();

    // if mode = 1, steps = 1; if mode = 2, steps = WALLY_COLS/ROWS / 2; if mode = 3, steps = WALLY_COLS/ROWS
	int stepX = mode == 1 ? 1 : mode == 2 ? wallyMatrix->getCols() /2 : wallyMatrix->getCols();// What should the size of the steps be in the x direction
	int stepY = mode == 1 ? 1 : mode == 2 ? wallyMatrix->getRows() /2 : wallyMatrix->getRows();// What should the size of the steps be in the y direction

    std::vector<NNSScore> scoreList;

    /*
		Apparently the wally hidden in the image cannot be found using a linear search
			in chunks that equal it's size. So, I've decided to do half it's size
			because I'm more likely to find wally.. I originally itterated over all
			pixels.. That was a mistake (it took hours to process). This method
			takes minutes/seconds and, gives the result I expect (I found wally). So,
			I'm keeping it in... There's probably a much better way to do this...
	*/
	std::clock_t start = std::clock();

    int counter = 0;// The number of comparisons
	for (int y = 0; y <= imageH - wallyMatrix->getRows(); y += stepY ) {
        for(int x = 0; x <= imageW - wallyMatrix->getCols(); x += stepX){

			double pos = (y * imageW + x); // Where am I in the big matrix?

#ifndef VERBOSE // If we're not in debug mode, might as well print this nice percentage
			printf(mode == 1 ? "\r%.2f%% complete" : "\r%.0f%% complete",  (pos / (imageW * imageH)) * 100 ); // Ok.. Let's generate a % to show the user that i'm doing something
#endif
//			std::cout << "Currently at x=" << x << ", y=" << y << std::endl;

			//Get the image (the same size as wally) at this position.
            Matrix * testMatrix = clutteredMatrix->getSmallerImage(x, y, wallyMatrix);

            //clutteredMatrix->debugSmallerImage(x, y, testMatrix);
            //std::cout << "cooefficNormed for " << x << ","<< y << " : " << wallyMatrix->cooefficNormed(testMatrix) << std::endl;

			double score = wallyMatrix->coefficientNormed(testMatrix);

            scoreList.push_back({x, y, false, score});

            counter++;
            delete testMatrix; // Make sure the test matrix is released from memory (fix those pesky leaks!)
        }
    }

	std::clock_t end = std::clock();

	//std::cout << "Main Loop took " << (double(end - start) / CLOCKS_PER_SEC) << " seconds" << std::endl;

	std::cout << "\n" << counter << " comparisons made against the template image." << std::endl;
	//Sort the scores (uses the < operator)
    std::sort(scoreList.begin(), scoreList.end());

	FileHandler * ncF = new FileHandler(); // Create a file handler to write the images to a file

	if (top != 0) {
        std::cout << "\n\nI'm generating the PGM files for the best " << top << " matches.\nThe images will be labelled 1.pgm - " << top << ".pgm" << std::endl;
	}
	for (int i = 0; i < top; i++) { // Loop through the best N NC scores
        std::string topFilename = std::to_string(i+1) + ".pgm";

        char * topName = new char[topFilename.length() + 1];

        std::strcpy(topName, topFilename.c_str());

		// Let's get the image matrix that's associated with the current score
        Matrix * topMat = clutteredMatrix->getSmallerImage(scoreList[i].x, scoreList[i].y, wallyMatrix);

#ifdef VERBOSE
        printf("Score for %d,%d = %f\n", scoreList[i].x, scoreList[i].y, scoreList[i].score);
#endif

        ncF->writeMatrix(topName, topMat); // DO the same for the image matched with the SSD

		//Release the memory... Kind of like the Kraken except, useful.
        delete[] topName;
        delete topMat;
	}
    char filename[] = "scene.pgm";
    char wallyName[] = "wally.pgm";

    //Get the best match, using the coeff formula
    clutteredMatrix->debugSmallerImage(scoreList[0].x, scoreList[0].y, wallyMatrix);
    std::cout << "I have drawn a black square around Wally in the image \"scene.pgm\"" << std::endl;

    ncF->writeMatrix(filename, clutteredMatrix);
    ncF->writeMatrix(wallyName, wallyMatrix);

	// Make sure the filehandler is destroyed
	delete ncF;
	// Destory the main image matricies
	delete wallyMatrix;
	delete clutteredMatrix;

	std::cout << "The program has finished." << std::endl;

    return 0;
}
