import numpy as np

# Assuming list_of_predictions_lists is your 2D numpy array
# Sample list_of_predictions_lists for demonstration purposes
list_of_predictions_lists = np.array([
    np.array([1, 2, 3]),
    np.array([]),
    np.array([4, 5]),
    np.array([]),
    np.array([6, 7, 8])
], dtype=object)

# Calculate the averages and handle empty arrays
averages_with_none = np.array([np.mean(arr) if len(arr) > 0 else None for arr in list_of_predictions_lists.flatten()], dtype=object)

# Reshape the resulting array to match the original shape
averages_with_none = averages_with_none.reshape(list_of_predictions_lists.shape)

print(averages_with_none)
