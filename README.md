# two-means-trees

Code to build an unsupervised random forest, using 2-means as splitting method at each node.

To compile: g++ -std=c++11 TwoMeansTree.cpp -o TwoMeansTree

Python bindings:

1. Install pybind11
2. g++ -I/usr/include/python3.5m -O3 -shared -std=c++11 -fPIC `python3 -m --includes` TwoMeanTree.h TwoMeanTree.cpp bindings.cpp -o twomeantree`python3-config --extension-suffix`

