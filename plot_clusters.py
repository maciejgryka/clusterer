import numpy as np
from mayavi.mlab import points3d

points = np.genfromtxt('data.csv', delimiter=',')
means = np.genfromtxt('means.csv', delimiter=',')
points3d(points[:,0], points[:,1], points[:,2], color=(1,1,1), mode='2dvertex')
points3d(means[:,0], means[:,1], means[:,2], color=(1,0,0), scale_factor=0.2)