import pandas as pd
import numpy as np

# Create a small example DataFrame
data = {
    'A': [1000, 2000, np.nan, 4000, 5000],
    'B': [np.nan, 20, 30, np.nan, 50],
    'C': [10, np.nan, 30, 40, 50]
}

df = pd.DataFrame(data)
cols_to_fill = ['A', 'B', 'C']

# Fill NaN values with the average value in each column
df[cols_to_fill] = df[cols_to_fill].fillna(df[cols_to_fill].mean())

print(df)
