import numpy as np

t0 = np.array(10)
print("tensor: %s, dim: %d" % (t0, t0.ndim)) 

t1 = np.array([1, 2, 3])
print("tensor: %s, dim: %d" % (t1, t1.ndim)) 

t2 = np.array([[1, 2], [3, 4]])
print("tensor: %s, dim: %d" % (t2, t2.ndim)) 
