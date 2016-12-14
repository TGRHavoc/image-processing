## Image Processor


### Compiling the program

To compile the program using Visual Studio, open the vcxproj file.
Once the project has opened you can compile by going to `Build > Build Solution`.

To compile the program on Linux, make sure you have [G++](https://gcc.gnu.org/) installed on the system.
Then you can run the compile script by running `./compile.sh` in the terminal.

### Running the program

Depending on which method you used to compile the program, this will be slightly different.

If you compiled the program using Visual Studio, navigate to the project folder (where the source code is located) and open the Debug folder.
In this folder there should be a `.exe` file that you can run.

If you compiled the program on Linux, you need to change your directory to the output folder by doing `cd output/`.
Then you can run the program using the command `./a.out`.


###### Note: Please make sure you copy the text files (`Wally_grey.txt` and `Cluttered_scene.txt`) from the resources folder into the same directory as the program you're running.
