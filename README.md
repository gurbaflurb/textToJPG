# TEXT TO A PPM!!!!!!!

## Take all your favorite texts and convert them to the more reliable format of ppm

### Run the `make` command on the command line to compile or
### compile on Linux `g++ -pthread textToPPM.cpp -o main`
### compile on windows using cygwin or visual studio

## Changelog
V1.2 More Changes!
- Re-added spinner and fixed threading issues
- Adjusted Image size from 255x255 to 2048x2048
- Added basic command line arguments, doesn't do paths to files or file input
- Added makefile

V1.1 Images generated are now sudo random
- Removed Spinner until a solution is found
- Fixed image pattern generation to be based on input text

V1.0 Converts only input text to a ppm in a not so random format
### - Known Issues
- Throws errors when quitting because of thread management
- Spinner Spins very iradically
- Images generated are all very similar