import pandas as pd
import numpy as np
from matplotlib import pyplot as plt
from sklearn.linear_model import LogisticRegression, LogisticRegressionCV
from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.preprocessing import StandardScaler, RobustScaler, LabelEncoder, OneHotEncoder
from sklearn.pipeline import make_pipeline
from sklearn.metrics import roc_auc_score

# Для вашего удобства списки с именами разных колонок

# Числовые признаки
num_cols = [
    'ClientPeriod',
    'MonthlySpending',
    'TotalSpent'
]

# Категориальные признаки
cat_cols = [
    'Sex',
    'IsSeniorCitizen',
    'HasPartner',
    'HasChild',
    'HasPhoneService',
    'HasMultiplePhoneNumbers',
    'HasInternetService',
    'HasOnlineSecurityService',
    'HasOnlineBackup',
    'HasDeviceProtection',
    'HasTechSupportAccess',
    'HasOnlineTV',
    'HasMovieSubscription',
    'HasContractPhone',
    'IsBillingPaperless',
    'PaymentMethod'
]

feature_cols = num_cols + cat_cols
target_col = 'Churn'

def GetData(filename='./train.csv'):
  return pd.read_csv(filename)

def has_empty_string(row):
    return any(cell == ' ' or cell == '' or cell == np.nan for cell in row)

def FindDefectRows(data):
  return data.apply(has_empty_string, axis=1)

def DeleteDefectRows(data, delete=True):
  old_shape = data.shape[0]
  data = data.replace(' ', np.nan)
  data = data.replace('', np.nan)

  if (not delete):
    for column in num_cols:
      data[column] = pd.to_numeric(data[column], errors='coerce')
      average_value = data[column].mean()
      data[column].fillna(average_value, inplace=True)

  data = data.dropna()
  new_shape = data.shape[0]
  delta = old_shape - new_shape
  print(delta, 'rows were deleted,', new_shape, 'remains')
  return data

def GetClearData(filename='./train.csv', delete=True):
  return DeleteDefectRows(GetData(filename), delete)

def OneHotEncoding(data):
  encoder = OneHotEncoder()
  encoded_data = encoder.fit_transform(data[cat_cols])
  encoded_data_df = pd.DataFrame(encoded_data.toarray(), columns=encoder.get_feature_names_out(input_features=cat_cols))
  data = pd.concat([data, encoded_data_df, data], axis=1)

  data.drop(cat_cols, axis=1, inplace=True)
  return data

def Scale(X_train, X_test):
  scaler = StandardScaler()
  X_train[num_cols] = scaler.fit_transform(X_train[num_cols])
  X_test[num_cols] = scaler.transform(X_test[num_cols])
  return X_train, X_test

def ScaleSingle(X_train):
  scaler = StandardScaler()
  X_train[num_cols] = scaler.fit_transform(X_train[num_cols])
  return X_train

def Split(data):
  X = data.iloc[:, :-1]
  y = data.iloc[:, -1]
  return X, y

if __name__ == "__main__":
  import time
  start_time = time.time()
  X, y = Split(GetClearData('./train.csv', False))
  X = OneHotEncoding(X)
  X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
  X_train, X_test = Scale(X_train, X_test)

  param_grid = {
      'C': np.linspace(2, 30, 100),
  }

  grid_search = GridSearchCV(LogisticRegression(max_iter=1000),
                            param_grid, cv=5,
                            scoring='roc_auc')

  grid_search.fit(X_train, y_train)

  y_pred = grid_search.predict_proba(X_test)[:, 1]

  print(grid_search.best_params_)
  roc_auc_score(pd.DataFrame(y_test).values, pd.DataFrame(y_pred).values)
  print("--- %s seconds ---" % (time.time() - start_time))