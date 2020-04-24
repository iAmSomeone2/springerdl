# Springer DL

Automatic PDF downloader application for a specific website.

## Required packages

* libcurl
* cmake
* make
* gcc

## Build instructions

1. Make a "build" directory in the root of the project and navigate into it.
2. Run `cmake ..` from the build directory to generate the CMake config files.
3. Run `make` to compile the project.
4. The compiled program will be in `build/src/` as `springerdl`

## Running the program

### Basic operation

* To do a basic run of the program: `./springerdl -i ./links.txt`
   * That will read a list of links (one per line) into memory, determine the actual target addresses, and download the appropriate files to the current directory (not yet implemented).

### Advanced Operation (Not yet implemented)

* Springer DL will have four usable flags: 
   * `i`: input file
   * `o`: output directory
   * `l`: file limit (100 of 400 files for example)
   * `t`: thread limit (max processor threads to give to the program)