# two-means-trees

Code to build an unsupervised random forest, using 2-means as splitting method at each node.

To compile: g++ -std=c++11 TwoMeansTree.cpp -o TwoMeansTree

Python bindings:

1. Install pybind11
2. g++ -I/usr/include/python3.5m -O3 -shared -std=c++11 -fPIC `python3 -m --includes` TwoMeanTree.h TwoMeanTree.cpp bindings.cpp -o twomeantree`python3-config --extension-suffix`
3. Example Usage:
Python 3.5.2 (default, Nov 23 2017, 16:37:01) 
[GCC 5.4.0 20160609] on linux
Type "help", "copyright", "credits" or "license" for more information.
import twomeantree
Xarr = [[1, 5, 7.8, 10.2, 15, 19, 21, 199, 200, 201, 202, 203, 204, 205]]
idxs = [1,2,3,4,5,6,7,8,9,10,11,12,13,14]
tree = twomeantree.buildTwoMeansTree(idxs, Xarr, 0, 4, 0)

