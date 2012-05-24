import numpy as np
from mayavi.mlab import points3d

def gaussian_blob(n_points, dimensionality, spread):
  blob = (
      np.random.randn(n_points, dimensionality) + 
      np.ones([1, dimensionality]) * np.random.rand(1, dimensionality) * 
      spread)
  return blob

k = 10 # number of clusters
points_per_blob = 5000
dimensionality = 3
spread = 20

# create data
points = np.zeros([k * points_per_blob, dimensionality])
for c in range(k):
  # put all the points in a single array
  points[c*points_per_blob:(c+1)*points_per_blob, :] = gaussian_blob(
      points_per_blob,
      dimensionality,
      spread)
# randomize point order - this is important for sequential k-means, as the first
# k points are taken as initializations for cluster centers - if they all come
# from the same cluster, the algorithm performs poorly
np.random.shuffle(points)
# save to disk
np.savetxt('blobs.csv', points, delimiter=',', fmt='%5.7f')
# display points in 3d
points3d(points[:,0], points[:,1], points[:,2], mode='2dvertex', color=(1,1,1))

