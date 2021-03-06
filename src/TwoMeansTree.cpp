#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include <queue>
#include <cstdlib>
#include <assert.h>
#include <algorithm> //sort
#include <limits>
#include <numeric> //accumulate
#include <string.h> //strcmp
#include <memory> //unique_ptr
#include <unordered_map>
#include <utility> //pair
#include <TwoMeansTree.h>

using namespace std;

/* store pairs of indices (i,j) for each pair 
of vertices that occur in a leaf node, and the number
of times they co-occur */ 
//vector< tuple< int, int, int> > pointleafoccurrences; 

unordered_map< int, vector< pair<int , int> > > coOccurMap;

bool greaterSecondInPair( pair<int, int> a, pair<int, int> b){
	return a.second > b.second;
}


TwoMeansTreeNode::TwoMeansTreeNode(vector< vector<double> > pts, unsigned int d, bool isLeafNode, int id){
			if(isLeafNode){
			    //set points at this node
			    for(int i=0; i<pts.size();i++){
			    	points.push_back(pts[i]);
			    } 
			    leafNode = true;
			    ID = id;
			    //cout << "added points to leaf node"<<endl;
			} else {
				leafNode = false;
				assert(pts.size() == 1);
				if((pts[0]).size() != 1){
					//cout << "(pts[0]).size() = "<<(pts[0]).size()<<endl;
					//cout << "Internal node only stores one point, the midpoint. "<<endl;
				}
				midpoint = pts[0][0];
				splitDim = -1;
				ID = id;
			}
			left = NULL;
			right = NULL;
			depth = d;
		} 
		
TwoMeansTreeNode::~TwoMeansTreeNode(){
/*
			delete this->right;
			delete this->left;
*/
		}
		
		void TwoMeansTreeNode::setRightChild(TwoMeansTreeNode* t1){
			this->right = t1;
		}
	
		void TwoMeansTreeNode::setLeftChild(TwoMeansTreeNode* t2){
			this->left = t2;
		}
	
		void TwoMeansTreeNode::setSplitDim(int splitdim){
			this->splitDim = splitdim;
		}
		
		int TwoMeansTreeNode::getSplitDim(){
			return this->splitDim;
		}
		
		unsigned int TwoMeansTreeNode::getDepth(){
			return this->depth;
		}
		
		TwoMeansTreeNode* TwoMeansTreeNode::getLeftChild(){
			return this->left;
		}
		
		TwoMeansTreeNode* TwoMeansTreeNode::getRightChild(){
			return this->right;
		}
	
		vector< vector<double> > TwoMeansTreeNode::getPoints(){
			return this->points;
		}
		
		double TwoMeansTreeNode::getMidpoint(){
			return this->midpoint;
		}
		
		bool TwoMeansTreeNode::isLeafNode(){
			return this->leafNode;
		}
		
		int TwoMeansTreeNode::getID(){
			return this->ID;
		}


bool occurCountGreaterThan(pair< vector<double>, int > a, pair< vector<double>, int > b){
	return a.second > b.second;
}

void printCoOccurMap(int datasetsize){
	stringstream ofss;
	ofss<<"coOccurMap_"<<datasetsize<<"_pts.txt";
	cout << "printing leaf coOccurMap to file: "<<ofss.str()<<endl;
	ofstream coOccur_file;
	coOccur_file.open(ofss.str().c_str());
	for(auto i = 0; i<datasetsize; i++)
	{	
		auto found = coOccurMap.find (i);
		if(found != coOccurMap.end()){
			auto pairvec = coOccurMap.at(i);
			coOccur_file << i <<endl;
			for(int j=0; j<pairvec.size(); j++){
				pair< int, int > countpair = pairvec[j];
				coOccur_file << " ("<<countpair.first<<", "<<countpair.second<<"), ";
			}
			coOccur_file <<endl;
		}
	}
}

void printLevelOrder(TwoMeansTreeNode *tnode)
{
    // Base Case
    if (tnode == NULL)  return;
 
    // Create an empty queue for level order tarversal
    queue<TwoMeansTreeNode *> q;
 
    // Enqueue Root and initialize height
    q.push(tnode);
 
    while (q.empty() == false)
    {
        TwoMeansTreeNode *node = q.front();
        if(node->isLeafNode()){
		cout << " [num. pts ="<< (node->getPoints()).size() <<" ] ";
        } else {
		cout << " [midpoint at depth "<<node->getDepth()<<":  "<<node->getMidpoint()<<"] ";
	}
	q.pop();
 
        /* Enqueue left child */
        if (node->getLeftChild() != NULL)
            q.push(node->getLeftChild());
 
        /*Enqueue right child */
        if (node->getRightChild() != NULL)
            q.push(node->getRightChild());
    }
}
 

void printTree(TwoMeansTreeNode *tree){
	assert( (tree->getLeftChild()== NULL && tree->getRightChild() == NULL ) || (tree->getLeftChild()!= NULL && tree->getRightChild() != NULL));
	if( tree->getLeftChild() == NULL && tree->getRightChild()==NULL ){
		vector< vector<double> > pts = tree->getPoints();
		if(pts.size()==0) cout << "Warning: Leaf node with no points."<<endl;
		cout << "Leaf node "//<< tree->getID() 
			<<"points at depth "<<tree->getDepth() <<": <";
		for(int i=0; i<pts.size(); i++){
			cout <<" * ";
			cout <<": (";
			for(int j=0; j<(pts[i]).size(); j++){
				//cout << ", " << (pts[i])[j];
				printf("%f10.0, ",(pts[i])[j] );
			}
			cout <<"), ";
		}
		cout <<">"<<endl;
	} else {
		cout <<"Internal node "//<< tree->getID() 
			<<" at depth " << tree->getDepth(); 
			//<<" midpoint: "<<tree->getMidpoint()<<endl;
			printf("midpoint: %f10 \nsplitting dimension: %d",  tree->getMidpoint(), tree->getSplitDim() );
		cout<<endl;
		unsigned int depthcurrent = tree->getDepth();
		if(depthcurrent==0){
			cout << depthcurrent<<"--";
		}
		printTree(tree->getLeftChild());
		printTree(tree->getRightChild());		
	}
	return;
}

double euclideanDistance(vector< double > a, vector< double > b){
	assert(a.size() == b.size());
	vector<double> sqdists(a.size(), 0.0);
	for(int i=0; i<a.size(); i++){
		sqdists[i] = (a[i]-b[i])*(a[i]-b[i]);
	}
	double dist = sqrt(accumulate(sqdists.begin(), sqdists.end(), 0.0));
	return dist;
}

void printLeafNodes(TwoMeansTreeNode *tree){	
	if( tree->getLeftChild() == NULL && tree->getRightChild()==NULL ){
		vector< vector<double> > pts = tree->getPoints();
		cout << "Leaf node "//<< tree->getID() 
			<<"points:\n "<<endl;
		for(int i=0; i<pts.size(); i++){
			cout << "(";
			for(int j=0; j<(pts[i]).size(); j++){
				if(j<(pts[i]).size()-1){
					cout << pts[i][j] <<",";
				} else {
					cout << pts[i][j] <<")";
				}
			}
			if(i<pts.size()-1){
				cout << ", ";		
			}
		}
		cout <<endl;
	} else {
		printLeafNodes(tree->getLeftChild());
		printLeafNodes(tree->getRightChild());		
	}
	return;
}

/* twoMeansOneD: 
 *	finds the optimal 2-means clustering 
 * 	of data in one dimension
 *	returns a pair that holds the
 * 	sum of squared distances from points
 *	in each cluster to their
 *	means, and the midpoint
 *	between the boundaries of the two
 *	clusters  
 */
pair< double, double > twoMeansOneD(vector<double> X){
	int npts = X.size();
	//cout << "twoMeansOneD: number of input points = "<<npts<<endl;
 	
	/* process points in sorted order */	
	sort(X.begin(), X.end());
	double midpoint;
	vector<double> means;
	vector<double>::iterator it=X.begin();
	//initialize the two means
	double mean1=0.0, mean2=0.0, sum1=0.0, sum2=0.0;
	vector<double>::iterator it2 = X.begin();
	while(it2<X.end()){
		sum2 += *it2;
		it2++;
	}
	if(npts<4){
		for(int i=0; i<npts; i++){
			cout << "point "<<i<<" = "<<X[i]<<endl;
		}
		cout << "initialization: sum2 = "<<sum2<<endl;
	}
	mean2 = sum2/(double) npts;
	/* initially, set2 contains all points
	 *	and set1 contains no points 	*/
	int seenpts=0;
	double sumsqdists=0.0, minsumsqdists=numeric_limits<double>::max();
	while(seenpts<(npts-1)){
		if(npts<4) cout << "seen pts = "<<seenpts<<endl;
		seenpts++;
		/* adjust sums */
		sum1+=*it;
		sum2-=*it;
		/* adjust means */
		mean1 = sum1/(double) seenpts;
		if(npts<4) cout << "mean1 = "<<mean1<<endl;
		mean2 = sum2/(double) (npts-seenpts);
		if(npts<4) cout << "mean2 = "<<mean2<<endl;
		//cout << "iteration "<<seenpts<<": means found: mean1="<<mean1<<", mean2="<<mean2<<endl;
		//cout << " sum1="<<sum1<<", sum2="<<sum2<<endl;	
		
	
		/* assign points to closest mean and update sumsqdists */
		sumsqdists=0.0;
		for(int i=0; i<npts; i++){
			double dist1 = fabs(X[i] - mean1);
			double dist2 = fabs(X[i] - mean2);
			if(dist1<dist2){
				sumsqdists += dist1*dist1;
			} else {
			   	sumsqdists += dist2*dist2;
			}
		}
	
		/* store means if sum of squared distances
		* to means yields best split
		*/
		if(sumsqdists<minsumsqdists){
			minsumsqdists = sumsqdists;
			double meanofmeans = (mean1+mean2)/2;
			midpoint = (*it+*(it+1))/2.0; //midpoint is midpoint between the borders of the clusters represented by the two means
			if(npts<4) cout << "midpoint = "<<midpoint<<endl;
		 	/*	
			cout << "min sum sq. dists = "<<minsumsqdists<<endl;
			cout << "mean1 = "<<mean1;
			cout << ", mean2 = "<<mean2<<endl;
			cout << "midpoint = "<<midpoint<<endl;
			cout << "mean of means = "<<meanofmeans<<endl;
			*/
		}
		it++;
	}	
	//cout << "twoMeansOneD: returning midpont " <<midpoint<<endl;
	return make_pair(minsumsqdists, midpoint);
}

/* perform 2-means clustering on a set of 
	input data X
	return the two means 
*/
vector< vector<double> > twomeans(vector< vector<double> > X){	
	int npts = X.size();
	int ndims=0;
	if(!X.empty()){
		ndims = (X[0]).size();
	} 
	bool isCloserToMean1[npts];	
	//choose starting means at random from the points in the data set
	int idx1 = rand() % npts;
	int idx2 = rand() % npts;	
	vector< double > mean1 = X[idx1];
	vector< double > mean2 = X[idx2];
	//keep track of how many swaps happened 
	// between this iteration and the last
	int nSwaps = npts;
	int iters=0, maxiterations=1000;
	while (nSwaps>0 && iters<maxiterations){ //iterate until no points are re-assigned or maximum number of iterations is reached
		//iteratively update means and re-assign points
		nSwaps = 0;
		iters++;
		// assign points to closest mean
		for(int i=0; i<npts; i++){
			double dist1 = euclideanDistance(X[i], mean1);
			double dist2 = euclideanDistance(X[i], mean2);
			if(dist1<dist2){
				if(isCloserToMean1[i] == false) nSwaps++;
				isCloserToMean1[i] = true;
			} else {
				if(isCloserToMean1[i] == true) nSwaps++;
				isCloserToMean1[i] = false;	
			}
		}
		// re-compute means
		mean1.clear();
		mean1.resize(ndims, 0.0);
		mean2.clear();
		mean2.resize(ndims, 0.0);
		double npts1 = 0.0, npts2 = 0.0;
		for(int i=0; i<npts; i++){
			if(isCloserToMean1[i]){ 
				for(int dim=0; dim<ndims; dim++){
					mean1[dim] += (X[i])[dim];
				}
				npts1++;
			} else { 
				for(int dim=0; dim<ndims; dim++){
					mean2[dim] += (X[i])[dim];
				}
				npts2++;
			}
		}
		for(int dim=0; dim<ndims; dim++){
			mean1[dim] = mean1[dim]/npts1;
		}
		for(int dim=0; dim<ndims; dim++){
			mean2[dim] = mean2[dim]/npts2;
		}
	}
	vector< vector<double> > means;
	means.push_back(mean1);
	means.push_back(mean2);
	return means;
}
	
void split_1D_DataBy2Means(vector<vector<double> > X, double midpt, bool *closerToMu1, int splitting_dimension){
	int n = X.size();
	int ndims=0;
	if(!X.empty()){
		ndims = X[0].size();
	}
	for(int i=0; i<n; i++){
		if(X[i][splitting_dimension] < midpt){
			closerToMu1[i] = true;	
		} else { // in this case d_mu1 >= d_mu2
			closerToMu1[i] = false;
		} 
	}
}

void splitDataBy2Means(vector<vector<double> > X, vector< vector<double> > mus, bool *closerToMu1){
	int n = X.size();
	int ndims=0;
	if(!X.empty()){
		ndims = X[0].size();
	}
	double d_mu1, d_mu2;
	for(int i=0; i<n; i++){
		d_mu1 = euclideanDistance(X[i] , mus[0]); 
		d_mu2 = euclideanDistance(X[i] , mus[1]);
		if(d_mu1 < d_mu2){
			closerToMu1[i] = true;	
		} else { // in this case d_mu1 >= d_mu2
			closerToMu1[i] = false;
		} 
	}
}
	
int chooseBestSplit(vector< vector<double> > Xs, vector<int> splitting_dim_candidates){
	/* project X's onto splitting dimension */
	vector<double> projectedXs;
	int npts = Xs.size();
	//cout <<"chooseBestSplit: number of input points = "<<npts<<endl;
	double sumsqdists, minsumsqdists=numeric_limits<double>::max();
	int bestSplitDim = -1;

	/* test each splitting dimension from set of candidates,
	* save the best splitting dimension in terms of k-means
	*  optimality */
	for(int j=0; j<splitting_dim_candidates.size(); j++){
		int splitting_dim = splitting_dim_candidates[j];
		for(int i=0; i<npts; i++){
			projectedXs.push_back(Xs[i][splitting_dim]);
		}
		/* split points by 2-means in one dimension */	
		pair< double, double > sqdistsmidptpair = twoMeansOneD(projectedXs);//twomeans(X);
		sumsqdists = sqdistsmidptpair.first;
		//cout << "chooseBestSplit: sumsqdists at dimension"
		//<<splitting_dim<<" = "<<sumsqdists<<endl;
		if(sumsqdists < minsumsqdists){
			minsumsqdists = sumsqdists;
			bestSplitDim = splitting_dim;
		}
		projectedXs.clear();
	}
	//cout << "chooseBestSplit: best splitting dim = "<<bestSplitDim;
	//cout <<", minsumsqdists = "<<minsumsqdists<<endl;
	return bestSplitDim;
}

vector<double> projectOntoOneDim(vector< vector<double> > X, int splitdim){
	if(splitdim<0){
		//cout << "splitting dimension must be >=0 "<<endl;
		exit(0);
	}
	vector<double> projectedXs;
	for(int i=0; i<X.size(); i++){
		projectedXs.push_back(X[i][splitdim]);
	}
	return projectedXs;
}

TwoMeansTreeNode * buildTwoMeansTree(vector<int> indices, vector< vector<double> > X, unsigned int d, unsigned int depth_threshold, int idparent){
	int npts = X.size();
	//cout << "X.size() = "<<X.size()<<endl;
	//cout << "indices.size() = "<<indices.size()<<endl;
	int min_pts_in_leaf = 1;
	//cout << "npts = "<<X.size()<<endl;
	/* split criteria: stop splitting when number 
	 *	of points in a node is low, or when
	 * 	depth limit is met
	*/
	if(d>=depth_threshold || npts <= min_pts_in_leaf){
		//cout << "d>="<<depth_threshold<<" or "<<npts<<"<=2"<<endl;
	}
	if(d>=depth_threshold || npts <= min_pts_in_leaf){
		//cout << "creating new leaf node with "<<npts<<" points "<<endl;
		TwoMeansTreeNode * leafnode = new TwoMeansTreeNode(X, d, true, idparent);
		/* store the indices of points that co-occur
			in the leaf node */
		vector<int> uniqueindices;
		uniqueindices = indices;
		cout << "leaf node: indices.size() = "<< indices.size()<<endl;
		cout << "indices: ";
		for(int index=0; index<indices.size(); index++){
			cout << indices[index]<<", ";
		}
		cout <<endl;
		sort(uniqueindices.begin(), uniqueindices.end());
		auto last = unique(uniqueindices.begin(), uniqueindices.end());	
		uniqueindices.erase(last,uniqueindices.end());
		cout << "leaf node: uniqueindices.size() = "<< uniqueindices.size()<<endl;
		/* for(int i=0; i<uniqueindices.size(); i++){
			cout << "idx "<<i<<" = "<<uniqueindices[i]<<", ";
		}*/
		cout<<endl;
		for(int it = 0; it<uniqueindices.size(); it++){
			int i = uniqueindices[it];
			//cout << "i = "<<i;
			for(int it2 = 0; it2<it; it2++){
				int j = uniqueindices[it2];
				//cout <<" j = "<<j<<endl;
				int numcooccurrences=0;
				if(j<i){
					auto found = coOccurMap.find (i);
					if ( found == coOccurMap.end() ){
						vector< pair<int, int> > jpair;
						jpair.push_back( make_pair(j, 1) );
						//cout << "adding pair ("<<j<<", 1)"<<endl;
						coOccurMap[i] = jpair;
					} else {
						auto pairvec = coOccurMap[i];
						int jidx;
						bool foundj = false;
						for(int k=0; k<pairvec.size(); k++){
							if((pairvec[k]).first==j){
								numcooccurrences = (pairvec[k]).second;
								jidx = k;
								foundj = true;			
							}
						}
						numcooccurrences++;
						//cout << "adding pair ("<<j<<", ";
						//cout << numcooccurrences<<")"<<endl;
						if(foundj) pairvec[jidx] = make_pair(j, numcooccurrences);
						else pairvec.push_back(make_pair(j, 1));
						coOccurMap[i] = pairvec;
					}
				}
			}
		}
		return leafnode;
	}
	
	int ndimensions;
	if(npts>0){
		ndimensions = (X[0]).size(); //assumes X's are all same dimensionality
	}
	
	/* Choose a random (with replacement) subset of fixed size
	   representing splitting dimension candidates */
	vector<int> splitting_dim_candidates;
	vector<int> dimensions;
	for(int j=0; j<ndimensions; j++){
		dimensions.push_back(j);	
	}
	
	/* shuffle the dimensions to get a random sample */
	random_shuffle(dimensions.begin(), dimensions.end());
	
	/* subset_dims_size is the number of dimensions to test 
	*	with one-dimensional k-means
	*/
	int subset_dims_size = (int) sqrt(ndimensions);
	//cout << "Dimension subset size = "<<subset_dims_size<<endl;
	for(int j=0; j<subset_dims_size; j++){
		//cout << "adding dimension "<<dimensions[j]<<endl;
		splitting_dim_candidates.push_back(dimensions[j]);
	}
	//cout << endl;
	
	/* choose best splitting dimension from among candidates */
	int splitting_dim = chooseBestSplit(X, splitting_dim_candidates);
	//cout << "splitting dimension at depth "<<d<<" = "<<splitting_dim<<endl;
	
	/* project onto splitting dimension */	
	//cout << " projecting data onto splitting dimension "<<endl;
	vector<double> projectedXs = projectOntoOneDim(X, splitting_dim);
	
	/* perform 2-means clustering of data in one dimension */
	//cout << "computing means with 2-means"<<endl;
	pair< double, double> meanspair = twoMeansOneD(projectedXs);//twomeans(X);
	double midpt = meanspair.second;
	vector< vector<double> > midptVec;
	vector<double> midptV;
	midptV.push_back(midpt);
	midptVec.push_back(midptV);
	
	/* split data based on 2-means partitioning */
	//cout << "splitting data"<<endl;
	bool closertoMu1[npts];
	split_1D_DataBy2Means(X, midpt, closertoMu1, splitting_dim);
	//splitDataBy2Means(X, means, closertoMu1);
	//cout << "split data of size "<<npts<<"by 2-means."<<endl;	
	vector< vector<double> > leftsplit;
	vector<int> leftindices;
	vector< vector<double> > rightsplit;
	vector<int> rightindices;
	int nleft=0, nright=0;
	for(int i=0; i<X.size(); i++){
		if(closertoMu1[i]){
			leftsplit.push_back(X[i]);
			leftindices.push_back(indices[i]);
			nleft++;
		} else {
			rightsplit.push_back(X[i]);
			rightindices.push_back(indices[i]);
			nright++;
		}
	}
	if(leftsplit.size()==0 || rightsplit.size()== 0){ // in this case all 1-D projections were equivalent
		TwoMeansTreeNode * leafnode = new TwoMeansTreeNode(X, d, true, idparent);
		return leafnode;
	}
	//cout << "splitting: "<<nleft<<" points left and "<<nright<<" points right"<<endl;
	
	/* recurse on left and right sides of tree */
	TwoMeansTreeNode * leftsubtree = buildTwoMeansTree(leftindices, leftsplit, d+1, depth_threshold, idparent+1);
	TwoMeansTreeNode * rightsubtree = buildTwoMeansTree(rightindices, rightsplit, d+1, depth_threshold, idparent+2);
	TwoMeansTreeNode * root = new TwoMeansTreeNode(midptVec, d, false, idparent);
	root->setLeftChild(leftsubtree);
	//cout << "set left child "<<endl;
	root->setRightChild(rightsubtree);
	//cout << "set right child"<<endl;
	root->setSplitDim(splitting_dim);
	return root;	
}

/* numPoints: returns the number of points
	stored in the leaves of a TwoMeansTreeNode 
	tree
*/
int numPoints(TwoMeansTreeNode* tree){
	if(tree->getLeftChild() == NULL && tree->getRightChild()==NULL){
		vector< vector<double> > leafpoints = tree->getPoints();
		return leafpoints.size();
	} else {
		return (numPoints(tree->getLeftChild()) + numPoints(tree->getRightChild()));
	}
}

/* getRandomSample:
 *	return a sample of a given size, drawn from X
 *	with replacement
 */
vector< vector<double> > getRandomSample(vector< vector<double> > X, int size, int ** appearsInTree, int treeID){
	vector< vector<double> > Xs;
	vector< vector<double> > subsetXs;
	for(int i=0; i<X.size(); i++){
		Xs.push_back(X[i]);
	}
	for(int i=0; i<size; i++){
		int randidx = rand()%size;
		/*cout << "adding random point (";
		for(int j=0; j<Xs[randidx].size(); j++){
			cout << Xs[randidx][j]<<" ";
		}
		cout <<")"<<endl;*/
		subsetXs.push_back(Xs[randidx]);
		appearsInTree[randidx][treeID]++;
	}
	return subsetXs;
}

/* getRandomSampleIndices: 
*	return a vector of integers that is a
* 	random sample, with replacement, from 
*	the numbers 0 to n
*/
vector<int> getRandomSampleIndices(int n, int ** appearsInTree, int treeID){
	vector<int> indices;
	for(int i=0; i<n; i++){
		int randidx = rand()%n;
		//cout << "  adding random point "<< randidx << endl; 
		indices.push_back(randidx);
		appearsInTree[randidx][treeID]++;
	}
	return indices;
}

vector< TwoMeansTreeNode * > buildRandomForest(vector< vector<double> > X, int numTrees, unsigned int depthThreshold, int ** appearsInTree){
	
	vector< TwoMeansTreeNode* > forest;
	for(int i=0; i<numTrees; i++){
		/* bagging: get a random sample, with replacement, from X */
		vector<int> randindices = getRandomSampleIndices(X.size(), appearsInTree, i);
		cout << "sample size for tree "<<i<<" = "<<randindices.size()<<endl;
		vector< vector<double> > sampleXs;
		for(int j=0; j<randindices.size(); j++){
			sampleXs.push_back( X[randindices[j]] );
		}
		//vector< vector<double> > sampleXs = getRandomSample(X, X.size(), appearsInTree, i);
		TwoMeansTreeNode * tree = buildTwoMeansTree(randindices, sampleXs, 0, depthThreshold, 0);
		forest.push_back(tree);
		cout << "finished tree "<<i<<endl;
	}
	return forest;
}

TwoMeansTreeNode* classLeaf(vector<double> x, TwoMeansTreeNode* t){
	if(t->isLeafNode()){	
		return t;	
	} else {
		int splitdim = t->getSplitDim();
		double midpt = t->getMidpoint();
		if(x[splitdim] < midpt){
			return classLeaf(x, t->getLeftChild());
		} else {
			return classLeaf(x, t->getRightChild());
		}	
	}
}

vector< vector<double> > kNearestNeighbors(vector<double> x, int k, vector<TwoMeansTreeNode*> forest){
	vector< vector<double> > neighbors;
	const int ntrees = forest.size();
	/* run the point down each tree, and record how many
		times each point co-occurs with the point 
		the nearest neighbors are those which 
		co-occured most frequently with the input
		point x */
	vector< vector<double> > leafpoints;
	//unordered_map< vector<double> , int> coOccurMap;
	vector< pair<vector<double>, int> > coOccurCounts; 
	vector< vector<double> > uniqueNeighbors;
	int maxCoOccurrences = 0;
	
	
	for(int t=0; t<ntrees; t++){
		TwoMeansTreeNode* leaf = classLeaf(x, forest[t]);
		vector< vector<double> > leafpoints = leaf->getPoints();
		for(int i=0; i<leafpoints.size(); i++){
			vector<double> y = leafpoints[i];
			//unordered_map< vector<double>, int >::const_iterator found = coOccurMap.find(y);
  			vector< vector<double> >::iterator found = find(uniqueNeighbors.begin(), uniqueNeighbors.end(), y);
			//if ( found == coOccurMap.end() ){
			if ( found == uniqueNeighbors.end() && y != x ){
				//coOccurMap.insert(make_pair< vector<double>, int>(y, 1));
				uniqueNeighbors.push_back(y);
				const vector<double> y2 = y;
				pair< vector<double> , int > newpair = make_pair(y2, 1);
				coOccurCounts.push_back(newpair);
				if(maxCoOccurrences==0){
					maxCoOccurrences=1;
				}
			} else if( y != x) { /* ensure that nearest neighbor isn't the point itself */
				//coOccurMap.at(y)++;
				int foundidx = found - uniqueNeighbors.begin();
				(coOccurCounts[foundidx]).second++;
				if(coOccurCounts[foundidx].second > maxCoOccurrences){
					//maxCoOccurrences = coOccurMap.at(y);
					maxCoOccurrences = (coOccurCounts[foundidx]).second;
				}
			}
		}
	}
	
	//for(auto& y::coOccurMap){
	//for(int i=0; i<coOccurCounts.size(); i++){
		//pair< vector<double>, int> y = coOccurCounts[i];
	
	sort(coOccurCounts.begin(), coOccurCounts.end(), occurCountGreaterThan);
	
	for(int j=0; j < k; j++){
		neighbors.push_back((coOccurCounts[j]).first);
	}
	
	return neighbors;	
}

vector<double> nearestNeighbor(vector<double> x, vector<TwoMeansTreeNode*> forest){
	vector< vector<double> > neighbors;
	const int ntrees = forest.size();
	/* run the point down each tree, and record how many
		times each point co-occurs with the point 
		the nearest neighbors are those which 
		co-occured most frequently with the input
		point x */
	vector< vector<double> > leafpoints;
	//unordered_map< vector<double> , int> coOccurMap;
	vector< pair<vector<double>, int> > coOccurCounts;
	//vector< pair<vector<double>, int> > coOccurCounts(sizey, make_pair(vector<int>(y), 0)); 
	vector< vector<double> > uniqueNeighbors;
	int maxCoOccurrences = 0;
	for(int t=0; t<ntrees; t++){
		TwoMeansTreeNode* leaf = classLeaf(x, forest[t]);
		vector< vector<double> > leafpoints = leaf->getPoints();
		for(int i=0; i<leafpoints.size(); i++){
			vector<double> y = leafpoints[i];
			//unordered_map< vector<double>, int >::const_iterator found = coOccurMap.find(y);
  			vector< vector<double> >::iterator found = find(uniqueNeighbors.begin(), uniqueNeighbors.end(), y);
			//if ( found == coOccurMap.end() ){
			if ( found == uniqueNeighbors.end() && y != x ){
				//coOccurMap.insert(make_pair< vector<double>, int>(y, 1));
				uniqueNeighbors.push_back(y);
				const vector<double> y2 = y;
				pair< vector<double> , int > newpair = make_pair(y2, 1);
				coOccurCounts.push_back(newpair);
				if(maxCoOccurrences==0){
					maxCoOccurrences=1;
				}
			} else if( y != x) { /* ensure that nearest neighbor isn't the point itself */
				//coOccurMap.at(y)++;
				int foundidx = found-uniqueNeighbors.begin();
				(coOccurCounts[foundidx]).second++;
				if(coOccurCounts[foundidx].second > maxCoOccurrences){
					//maxCoOccurrences = coOccurMap.at(y);
					maxCoOccurrences = (coOccurCounts[foundidx]).second;
				}
			}
		}
	}
	
	//for(auto& y::coOccurMap){
	for(int i=0; i<coOccurCounts.size(); i++){
		pair< vector<double>, int> y = coOccurCounts[i];
		if(y.second == maxCoOccurrences){
			neighbors.push_back(y.first);
		}
	}
	
	if(neighbors.size()>1){
		random_shuffle(neighbors.begin(), neighbors.end());
	}
	vector<double> nearestNeighbor = neighbors[0];
	return nearestNeighbor;
}
	
bool appearInSameLeafNode(vector<double> a, vector<double> b, TwoMeansTreeNode* tree){
	bool foundadim[a.size()];
	bool foundbdim[b.size()];
	bool fa, fb, founda, foundb, foundaAndb=false;
	if( tree->isLeafNode() ){
		vector< vector<double> > pointsInLeafNode = tree->getPoints();
		founda = (find(pointsInLeafNode.begin(), pointsInLeafNode.end(), a)!=pointsInLeafNode.end());
		foundb = (find(pointsInLeafNode.begin(), pointsInLeafNode.end(), b)!=pointsInLeafNode.end());
		return ( founda && foundb );
	} else {
		int dim = tree->getSplitDim();
		double midpt = tree->getMidpoint();
		if( (a[dim] < midpt && b[dim] >= midpt) || (a[dim] >= midpt && b[dim] < midpt)){
			return false; // points are not on same side of split
		} else {
			return (appearInSameLeafNode( a,b,tree->getLeftChild() ) || appearInSameLeafNode( a,b,tree->getRightChild() ) );
		}
	}
}

int main(int argc, char **argv){
	std::vector<std::vector<double> > Xarr { { 144, 7, 6, 5 },
		                                    { 2, 24, 21, 5 } };
	vector<int> idxs = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
	TwoMeansTreeNode* tree = buildTwoMeansTree(idxs, Xarr, 0, 4, 0);
	cout << "Tree 1: "<< endl;
	printTree(tree);
	
}
