
#ifndef BruteForceKNN_hpp
#define BruteForceKNN_hpp

#include <algorithm> // sort, max, min
#include <math.h>    // pow, abs
#include <vector>    // vector<typename>
#include <queue>
#include <limits>    // numeric_limits<type>::max()
#include "Point.hpp"

/** A brute force approach to find K nearest neighbors */
class BruteForceKNN {

  protected:

    vector<Point> trainingPoints;
    int k;
    double threshold;

    // defining a data structure to store current K nearest neighbors
    priority_queue<Point, vector<Point>, CompareDist> kNN;
  public:
    /** Default constructor */
    BruteForceKNN() {}

    /** Initialize the training data points */
    void build(vector<Point>& points) {
      for(int i = 0; i < points.size(); i++) {
        trainingPoints.push_back(Point(points[i].features, points[i].label));
      }
    }

    /** Find k nearest neighbors of the given query point */
    vector<Point> findKNearestNeighbors(Point & queryPoint, unsigned int k) {
      kNN = priority_queue<Point, vector<Point>, CompareDist>(CompareDist());
      this->k = k;
      vector<Point> points;
      for(int i = 0; i < trainingPoints.size(); i++) {
        trainingPoints[i].setSquareDistToQuery(queryPoint);
        updateKNN(trainingPoints[i]);
      }
      while(!kNN.empty()) {
        points.push_back(kNN.top());
        kNN.pop();
      }

      return points;
    }

    /** Helper method to update your data structure storing KNN using
     * the given point. */
    void updateKNN(Point & point) {
      kNN.push(point);
      if(kNN.size() > this->k) {
        kNN.pop();
      }
      if(kNN.size() == this->k) {
        threshold = kNN.top().squareDistToQuery;
      }
    }    
};

#endif /* BruteForceKNN_hpp */
