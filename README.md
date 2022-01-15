# mandelbrot-set-bmp

A hybrid C program that generates a bmp image of the mandelbrot set

### Compilation
The program is meant for compilation on Linux systems.

To compile follow the steps below:
- make a new build directory 
```
mkdir build
```
- change directories to the newly created build directory
```
cd build/
```
- run cmake
```
cmake ../src/
make 
```

To run the program you must specify the width of the outputted image and it's name:
```
./main 1024 output.bmp
```
Width is specified in pixels and should be divisible by 4.


### Output example
![ExampleIgame](https://user-images.githubusercontent.com/74139325/149634433-174f66ff-89c5-408f-8a2e-e63e750502ef.jpg)
