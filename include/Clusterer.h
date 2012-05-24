#ifndef CLUSTERER_H
#define CLUSTERER_H

#include <vector>
#include <Eigen/Core>

// Class for clustering of data
// currently only sequential k-means algorithm is implemented - see
//http://www.cs.princeton.edu/courses/archive/fall08/cos436/Duda/C/sk_means.htm
class Clusterer {
public:
  Clusterer(int n_clusters):
      k_(n_clusters),
      cluster_points_(n_clusters, 0),
      n_points_(0) {
  };
  ~Clusterer() {};
  // add point and update means
  void AddPoint(const Eigen::RowVectorXf& point) {
  // if this is the first point we're adding, initialize means_
  if (n_points_ == 0) {
    means_ = Eigen::MatrixXf(k_, point.cols());
    means_.setRandom();
  }
  // if we have seen less points than clusters, assign this point to the first
  // empy cluster - this makes it converge faster than random initialization
  if (n_points_ < k_) {
    means_.row(n_points_) = point;
  }
  // find the closest mean index
  int closest_mean = FindClosestMean(point);
  // increment point counts
  cluster_points_[closest_mean] += 1.f;
  ++n_points_;
  // adjust the mean
  means_.row(closest_mean) += 
      (point - means_.row(closest_mean)) / cluster_points_[closest_mean];
}

  // same as above, but do it for each row in the given matrix
  void AddPoints(const Eigen::MatrixXf& points) {
    int n_new_points = static_cast<int>(points.rows());
    for (int r = 0; r < n_new_points; ++r) {
      AddPoint(points.row(r));
    }
  };
  // find which of means_ is closest to point
  int FindClosestMean(const Eigen::RowVectorXf& point) const {
  // compute distances from point to each mean
  Eigen::VectorXf norms((means_ - point.replicate(k_, 1)).rowwise().norm());
  // find the index of the closes mean
  int closest_mean = -1;
  float min_dist = FLT_MAX;
  for (int m = 0; m < k_; ++m) {
    if (norms(m) < min_dist) {
      min_dist = norms(m);
      closest_mean = m;
    }
  }
  return closest_mean;
}

  Eigen::MatrixXf means() const { return means_; };
private:

  int k_; // number of clusters
  Eigen::MatrixXf means_; // k-by-d; each row is a cluster center
  std::vector<float> cluster_points_; // number of points in each cluster
  int n_points_; // overall number of points added
  
  // not allowed
  Clusterer() {};
};

#endif // CLUSTERER_H