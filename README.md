# About this repository
This repository contains code to detect logs in images using ORB detector/descriptor with Bundle Min hashing.

# How to build
mkdir build; cmake .. ; make
This will create 3 executables "vocab", "index", "test"
# How to use 
The first argument to the command line is the root path to the Flickr Logos dataset.

./vocab $FLICKR_ROOT will create the descriptors and the vocabulary file
./index $FLICKR_ROOT will create the MinHash indices
./test $FLICKR_ROOT will load the test set and print out accuracy ( if some category has >25% votes ).
