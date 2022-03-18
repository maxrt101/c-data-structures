# c-data-structures
Common data structures implemented in c11.  

## Installation:
Prerequisites: `gcc` or `clang` & `make`  
Steps:  
  - Clone the repo
  - Run `make`
  - In `build/` folder you'll find `include/` folder with all header files and in `lib` - `libcds.a`

If you need to install cds into a different folder use `make PREFIX=/path/to/install/folder`  

## Tests:
To run tests execute `make test`  

## TODO/DONE:
 - [x] carray  - Dynamic array
 - [X] clist   - Linked list
 - [x] cstring - String wrapper
 - [ ] ctable  - Hash map
 - [ ] cbtree  - Binary tree
