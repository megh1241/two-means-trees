#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include"TwoMeanTree.h"

namespace py = pybind11;
using namespace std;

 
PYBIND11_MODULE(twomeantree, m) {
	m.doc() = "Python Bindings for TwoMeanTrees"; 
	m.def("greaterSecondInPair", &greaterSecondInPair);
	py::class_<TwoMeansTreeNode>(m, "TwoMeansTreeNode")
		.def(py::init<vector< vector<double> >, unsigned int, bool, int>())
		.def("setRightChild", &TwoMeansTreeNode::setLeftChild)
		.def("setLeftChild", &TwoMeansTreeNode::setRightChild)
		.def("setSplitDim", &TwoMeansTreeNode::setSplitDim)
		.def("getSplitDim", &TwoMeansTreeNode::getSplitDim)
		.def("getDepth", &TwoMeansTreeNode::getDepth)
		.def("getRightChild", &TwoMeansTreeNode::getLeftChild)
		.def("getLeftChild", &TwoMeansTreeNode::setRightChild)
		.def("getPoints", &TwoMeansTreeNode::getPoints)
		.def("getMidPoint", &TwoMeansTreeNode::getMidpoint)
		.def("isLeafNode", &TwoMeansTreeNode::isLeafNode)
		.def("getID", &TwoMeansTreeNode::getID);
	m.def("occurCountGreaterThan", &occurCountGreaterThan, "docstring");
	m.def("printCoOccurMap", &printCoOccurMap, "docstring");
	m.def("printLevelOrder", &printLevelOrder, "docstring");
	m.def("printTree", &printTree, "docstring");
	m.def("euclideanDistance", &euclideanDistance, "docstring");
	m.def("twoMeansOneD", &twoMeansOneD, "docstring");
        m.def("twomeans", &twomeans, "docstring");
	m.def("split_1D_DataBy2Means", &split_1D_DataBy2Means, "docstring");
	m.def("splitDataBy2Means", &splitDataBy2Means, "docstring");
	m.def("chooseBestSplit", &chooseBestSplit, "docstring");
	m.def("buildTwoMeansTree", &buildTwoMeansTree, "docstring");
	m.def("numPoints", &numPoints, "docstring");
	m.def("getRandomSample", [](vector< vector<double> > X, int size, 
		vector<vector<int>> appearsInTree, int treeID) {
			std::vector<int *> CappearsInTree;
			CappearsInTree.reserve(appearsInTree.size());
			for (auto &s : appearsInTree) 
				CappearsInTree.push_back(const_cast<int *>(s.data()));
			return getRandomSample(X, size, CappearsInTree.data(), treeID);
		});
	m.def("getRandomSampleIndices", [](int n, vector<vector<int>> appearsInTree, int treeID) {
		std::vector<int *> CappearsInTree;
		CappearsInTree.reserve(appearsInTree.size());
		for (auto &s : appearsInTree) 
			CappearsInTree.push_back(const_cast<int *>(s.data()));
		return getRandomSampleIndices(n, CappearsInTree.data(), treeID);
	});
	m.def("buildRandomForest", [](vector< vector<double> > X, int numTrees, 
				unsigned int depthThreshold, vector<vector<int>> appearsInTree) {
		std::vector<int *> CappearsInTree;
		CappearsInTree.reserve(appearsInTree.size());
		for (auto &s : appearsInTree) 
			CappearsInTree.push_back(const_cast<int *>(s.data()));
		return buildRandomForest(X, numTrees, depthThreshold, CappearsInTree.data());
	});

	m.def("classLeaf", &classLeaf, "docstring");
	m.def("kNearestNeighbors", &kNearestNeighbors, "docstring");
	m.def("nearestNeighbor", &nearestNeighbor, "docstring");
	m.def("appearInSameLeafNode", &appearInSameLeafNode, "docstring");

}
