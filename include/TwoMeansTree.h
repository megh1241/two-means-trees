#include <string>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <assert.h>
#include <utility> //pair

using namespace std;
class TwoMeansTreeNode {
	private:
		TwoMeansTreeNode *left;
		TwoMeansTreeNode *right;
		unsigned int depth;
		double midpoint;
		int splitDim; 
		vector< vector<double> > points;
		int ndimensions;
		bool leafNode;
		int ID;
	public: 
		TwoMeansTreeNode(vector< vector<double> > pts, 
				unsigned int d, bool isLeafNode, int id);
		~TwoMeansTreeNode();
		void setRightChild(TwoMeansTreeNode* t1);
		void setLeftChild(TwoMeansTreeNode* t2);
		void setSplitDim(int splitdim);
		int getSplitDim();
		unsigned int getDepth();
		TwoMeansTreeNode* getLeftChild();
		TwoMeansTreeNode* getRightChild();
		vector< vector<double> > getPoints();
		double getMidpoint();
		bool isLeafNode();
		int getID();
};

bool greaterSecondInPair( pair<int, int> a, pair<int, int> b);
bool occurCountGreaterThan(pair< vector<double>, int > a, 
		pair< vector<double>, int > b);
void printCoOccurMap(int datasetsize);
void printLevelOrder(TwoMeansTreeNode *tnode);
void printTree(TwoMeansTreeNode *tree);
double euclideanDistance(vector< double > a, vector< double > b);
void printLeafNodes(TwoMeansTreeNode *tree);
pair< double, double > twoMeansOneD(vector<double> X);
vector< vector<double> > twomeans(vector< vector<double> > X);
void split_1D_DataBy2Means(vector<vector<double> > X, double midpt, 
		bool *closerToMu1, int splitting_dimension);
void splitDataBy2Means(vector<vector<double> > X, 
		vector< vector<double> > mus, bool *closerToMu1);
int chooseBestSplit(vector< vector<double> > Xs, vector<int> splitting_dim_candidates);
vector<double> projectOntoOneDim(vector< vector<double> > X, int splitdim);
TwoMeansTreeNode * buildTwoMeansTree(vector<int> indices, vector< vector<double> > X,
	       	unsigned int d, unsigned int depth_threshold, int idparent);
int numPoints(TwoMeansTreeNode* tree); 
vector< vector<double> > getRandomSample(vector< vector<double> > X, 
		int size, int ** appearsInTree, int treeID);
vector<int> getRandomSampleIndices(int n, int ** appearsInTree, int treeID);
vector< TwoMeansTreeNode * > buildRandomForest(vector< vector<double> > X, 
		int numTrees, unsigned int depthThreshold, int ** appearsInTree);
TwoMeansTreeNode* classLeaf(vector<double> x, TwoMeansTreeNode* t);
vector< vector<double> > kNearestNeighbors(vector<double> x, int k, 
		vector<TwoMeansTreeNode*> forest);
vector<double> nearestNeighbor(vector<double> x, vector<TwoMeansTreeNode*> forest);
bool appearInSameLeafNode(vector<double> a, vector<double> b, TwoMeansTreeNode* tree);

