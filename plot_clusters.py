import numpy as np
from mayavi.mlab import points3d, text3d


def plot_clusters():
  points = np.genfromtxt('data.csv', delimiter=',')
  means = np.genfromtxt('means.csv', delimiter=',')
  points3d(
      points[:,0],
      points[:,1],
      points[:,2],
      color=(1,1,1),
      mode='2dvertex')
  points3d(means[:,0], means[:,1], means[:,2], color=(1,0,0), scale_factor=0.2)
  for mean in means:
    text3d(
        mean[0],
        mean[1],
        mean[2],
        text='({:01.1f}, {:01.1f}, {:01.1f})'.format(mean[0], mean[1], mean[2]),
        scale=0.5,
        color=(1,1,1))


if __name__ == "__main__":
  plot_clusters()