import pandas as pd

# Sample DataFrame with a datetime column
data = {'DateTime': ['2023-06-01 14:44:35.147', '2023-06-02 15:30:40.789', '2023-06-03 16:15:45.123']}
df = pd.DataFrame(data)

# Convert the 'DateTime' column to a datetime object with the specified format
df['DateTime'] = pd.to_datetime(df['DateTime'], format='%Y-%m-%d %H:%M:%S.%f')

# Convert the datetime to a float timestamp
# df['Timestamp_Float'] = df['DateTime'].values.astype(float)

# Convert the datetime to an integer Unix timestamp
df['DateTime'] = df['DateTime'].values.astype(int)

# Now, you have 'Timestamp_Float' and 'Timestamp_Int' columns with the float and int representations of the datetime.
print(df)
