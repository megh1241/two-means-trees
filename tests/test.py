import unittest
import two_means_trees as tmt
import numpy as np

class TestUM(unittest.TestCase):
 
    def setUp(self):
        pass
 
    def testTwoMeansTreeNode(self):
        pts = [[0.4, 0.6]]
        node_1 = tmt.TwoMeansTreeNode(pts, 1, False, 2)
        node_2 = tmt.TwoMeansTreeNode(pts, 2, True, 3)
        node_3 = tmt.TwoMeansTreeNode(pts, 2, True, 4)
        node_1.setLeftChild(node_2)
        node_1.setRightChild(node_3)
        self.assertEqual(node_2.getDepth(), 2)
        self.assertEqual(node_1.getDepth(), 1)
        self.assertEqual(node_1.getPoints(), [])
        self.assertEqual(node_1.getMidpoint(), 0.4)
        self.assertEqual(node_1.isLeafNode(), False)
        self.assertEqual(node_2.isLeafNode(), True)
 
    def testUtilities(self):
        a = [3.6, 2.3, 1.5, 0.6]
        b = [3.8, 2.9, 1.9, 0.9]
        self.assertEqual(np.allclose(tmt.euclideanDistance(a, b), 0.80622), True)
        self.assertEqual(tmt.occurCountGreaterThan((a, 5), (a, 10)), False)

    def testTwoMeans(self):
        x1 = [4.88, 1.23, 0.7, 9.9, 6.8, 12.6, 9.3, 4,5]
        x2 = [3.6, 0.6, 9.9, 2.2, 9.7, 10.11, 7.8, 2.3]
        x = [x1, x2]
        means_x1 = (33.83608, 5.9)
        test_x1 = tmt.twoMeansOneD(x1)
        print (test_x1)
        self.assertEqual(np.allclose(means_x1[0], test_x1[0]), True)
        self.assertEqual(np.allclose(means_x1[1], test_x1[1]), True)

    def testBuildTwoMeansTree(self):
        idxs = [1,2,3,4,5,6,7,8];
        idxs2 = [[1],[2],[3],[4],[5],[6],[7],[8]];
        tree = tmt.buildTwoMeansTree(idxs, idxs2, 0, 4, 0);
        print (tree.getMidpoint())
        tree2 = tree.getLeftChild()
        print (tree2.getMidpoint())
        print (tree2.getMidpoint())

        self.assertEqual(1,1)
 
if __name__ == '__main__':
    unittest.main()
