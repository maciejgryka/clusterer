import numpy as np
from mayavi.mlab import points3d


def gaussian_blob(n_points, dimensionality, spread):
  blob = (
      np.random.randn(n_points, dimensionality) + 
      np.ones([1, dimensionality]) * np.random.rand(1, dimensionality) * 
      spread)
  return blob


def create_data():
  points_per_blob = [10000, 5000, 5000, 5000, 1000, 500, 250, 125, 60, 25]
  k = len(points_per_blob) # number of clusters
  dimensionality = 3
  spread = 50 # how far the blobs are from each other
  # create data
  points = np.zeros([np.sum(points_per_blob), dimensionality])
  for c in range(k):
    start_index = np.sum(points_per_blob[:c])
    end_index = start_index + points_per_blob[c]
    # put all the points in a single array
    points[start_index:end_index, :] = gaussian_blob(
        points_per_blob[c],
        dimensionality,
        spread)
  # randomize point order - this is important for sequential k-means, as the 
  # first k points are taken as initializations for cluster centers - if they 
  # all come from the same cluster, the algorithm performs poorly
  np.random.shuffle(points)
  # save to disk
  np.savetxt('data.csv', points, delimiter=',', fmt='%5.7f')


if __name__ == "__main__":
  create_data()