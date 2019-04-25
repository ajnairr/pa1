#ifndef KDT_HPP
#define KDT_HPP

#include <algorithm> // sort, max, min
#include <math.h>    // pow, abs
#include <vector>    // vector<typename>
#include <queue>
#include <float.h>
#include "Point.hpp"

using namespace std;

/** A KD tree that can output K nearest neighbors of given query point */
class KDT {

  protected:

    /** Inner class that defines a KDNode with certain data point 
     *  and pointers to its children and parent
     */
    class KDNode {

      public:

        KDNode * left;
        KDNode * right;
        KDNode * parent;
        Point point;

        KDNode() {}

        KDNode(Point point) : point(point) {}
    };

    KDNode * root; // root of KD tree
    unsigned int numDim; // number of dimension of data points
    unsigned int k; // number of nearest neighbors to find
    double threshold; // largest distance to query point in current KNN
    unsigned int isize;
    unsigned int iheight;

    // TODO: define a data structure to store current K nearest neighbors
    priority_queue<Point, vector<Point>, CompareDist> kNN;
  
  public:

    /** TODO: Default constructor of KD tree */
    KDT() : root(nullptr), numDim(0), threshold(DBL_MAX), isize(0), 
                                                          iheight(0) {}

    ~KDT() {
      this->deleteAll(this->root);
      this->root = nullptr;
      this->numDim = 0;
      this->threshold = DBL_MAX;
      this->iheight = 0;
    }

    /** Build the KD tree from the given vector of Point references */
    void build(vector<Point>& points) {
      if(!points.empty()) {
        this->numDim = points[0].features.size();
      }
      this->root = buildSubtree(points, 0, points.size(), 0, 0);
    }

    /** Find k nearest neighbors of the given query point */
    vector<Point> findKNearestNeighbors(Point queryPoint, unsigned int k) {
      kNN = priority_queue<Point, vector<Point>, CompareDist>(CompareDist());
      this->k = k;

      findKNNHelper(root, queryPoint, 0);

      vector<Point> points;
      while(!kNN.empty()) {
        points.push_back(kNN.top());
        kNN.pop();
      }
      sort(points.begin(), points.end(), CompareLabel());
      return points;
    }

    /** Return the size of the KD tree */
    unsigned int size() {
      return isize;
    }

    /** Return the height of the KD tree */
    unsigned int height() {
      return iheight;
    }

  private:
    /** Helper method to recursively build the subtree of KD tree. */
    KDNode * buildSubtree(vector<Point>& points, unsigned int start, 
                        unsigned int end, unsigned int d, unsigned int height) {
      if(start >= end) {
        return nullptr;
      }
      else if(height > this->iheight) {
        this->iheight = height;
      }

      sort(points.begin() + start, points.begin() + end, CompareValueAt(d));
      unsigned int mid = (start + end) / 2;

      while(mid > start && points[mid - 1].features[d] ==
                           points[mid].features[d]) {
        mid--;
      }

      KDNode* node = new KDNode(points[mid]);
      this->isize++;
      node->left = buildSubtree(points, start, mid, (d + 1) % this->numDim,
                                                                    height + 1);
      if(node->left) {
        node->left->parent = node;
      }

      node->right = buildSubtree(points, mid + 1, end, (d + 1) % this->numDim,
                                                                    height + 1);
      if(node->right) {
        node->right->parent = node;
      }
      return node;
    }

    /** Helper method to recursively find the K nearest neighbors */
    void findKNNHelper(KDNode *node, const Point & queryPoint, unsigned int d) {
      if(!node) {
        return;
      }

      node->point.setSquareDistToQuery(queryPoint);
      if(kNN.size() < this->k || CompareDist()(node->point, kNN.top())) {
        updateKNN(node->point);
      }

      KDNode* closerTree;
      KDNode* furtherTree;
      if(queryPoint.features[d] < node->point.features[d]) {
        closerTree = node->left;
        furtherTree = node->right;
      }
      else {
        closerTree = node->right;
        furtherTree = node->left;
      }

      findKNNHelper(closerTree, queryPoint, (d + 1) % this->numDim);

      double dimDist = queryPoint.features[d] - node->point.features[d];
      if(kNN.size() < this->k || square(dimDist) < threshold) {
        findKNNHelper(furtherTree, queryPoint, (d + 1) % this->numDim);
      }
    }

    /** Helper method to update your data structure storing KNN using 
     *  the given point.
     */
    void updateKNN(Point & point) {
      kNN.push(point);
      if(kNN.size() > this->k) {
        kNN.pop();
      }
      if(kNN.size() == this->k) {
        threshold = kNN.top().squareDistToQuery;
      }
    }

    void deleteAll(KDNode* node) {
      if(!node) return;

      this->deleteAll(node->left);
      this->deleteAll(node->right);

      delete node;

      this->isize--;
    }
};
#endif // KDT_HPP
