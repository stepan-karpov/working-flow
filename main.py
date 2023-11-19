import numpy as np

def get_dominant_eigenvalue_and_eigenvector(data, num_steps):
    """
    data: np.ndarray – symmetric diagonalizable real-valued matrix
    num_steps: int – number of power method steps

    Returns:
    eigenvalue: float – dominant eigenvalue estimation after `num_steps` steps
    eigenvector: np.ndarray – corresponding eigenvector estimation
    """
    ### YOUR CODE HERE
    n = data.shape[0]
    current_r = np.random.rand(n)

    for i in range(0, num_steps):
        current_r = (1 / np.linalg.norm(data.dot(current_r))) * data.dot(current_r)

    return (current_r @ data.dot(current_r)) / (current_r @ current_r)

matrix = np.array([[5, 6, 3],
                  [-1, 0, 1],
                  [1, 2, -1]])

# 2, -2, 4

print(get_dominant_eigenvalue_and_eigenvector(matrix, 1000))