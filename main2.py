import numpy as np

def l2_distance(X_train, X_test):
    # Reshape the arrays to enable broadcasting
    X_train_reshaped = X_train[:, np.newaxis, :]
    X_test_reshaped = X_test[np.newaxis, :, :]

    # Compute squared differences and sum along the last axis
    squared_diff = (X_train_reshaped - X_test_reshaped)**2
    sum_squared_diff = np.sum(squared_diff, axis=-1)

    # Take the square root to get the L2 distance
    dists = np.sqrt(sum_squared_diff)

    return dists

# Example usage:
# Assuming X_train and X_test are arrays containing training and test points respectively
# Each row in X_train and X_test represents a point in the respective dataset

X_train = np.array([[1, 2], [3, 4], [5, 6]])
X_test = np.array([[7, 8], [9, 10]])

dists = l2_distance(X_train, X_test)
print(dists)
