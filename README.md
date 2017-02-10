## Image Processor

##### Note: This program only works for the supplies images at the minute.

### Compiling the program

Before compiling the program, first you need to make sure you have [CMake](https://cmake.org) installed on your system.

#### Windows

Run the `cmake` command from the same directory as the source files.
Once the command has finished, you should now have some project files that you can open in Visual Studio.
Once you have opened the project using Visual Studio you can compile it by going to `Build > Build Solution` or by pressing `Ctrl + Shift + B`.

#### Linux

Before running the cmake command, create a new directory for the program to be built into. You can do this by running the command `mkdir bin`

Now you have to change into the new directory and run the cmake command `cd bin && cmake ..`

Once the cmake command has completed you can compile the program by running the make command `make`

### Running the program

Depending on which method you used to compile the program, this will be slightly different.

If you compiled the program using Visual Studio, navigate to the project folder (where the source code is located) and open the Debug folder.
In this folder there should be a `.exe` file that you can run.

If you compiled the program on Linux, you can run the program using the command `./image_processing`.


###### Note: Please make sure you copy the text files (`Wally_grey.txt` and `Cluttered_scene.txt`) from the     `resources/` folder into the same directory as the program you're running.
