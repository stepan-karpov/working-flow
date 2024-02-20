def change_key_values(dictionary: dict):
  return dict(
    ((v, k) for k, v in dictionary.items()) 
  )

a = {
  1: 2,
  "FDGH": 1
}

print(change_key_values(a))