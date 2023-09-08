form_data = {}

try:
  name = form_data["name"]
except KeyError:
  print("error")
  raise
finally:
  print("finally")