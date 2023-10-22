from imblearn.over_sampling import SMOTENC
import pandas
# Example DataFrame with numerical and categorical features
data = {'feature1': [1, 2, 3, 4, 5],
        'feature2': ['A', 'B', 'A', 'C', 'B'],
        'target': [0, 0, 1, 1, 1]}
df = pandas.DataFrame(data)

# Extract numerical and categorical columns
numerical_cols = ['feature1']
categorical_cols = ['feature2']

# Apply SMOTENC to the data
smote_nc = SMOTENC(categorical_features=[1])  # Specify the indices of the categorical features
X_resampled, y_resampled = smote_nc.fit_resample(df.drop('target', axis=1), df['target'])