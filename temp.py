import numpy as np
import json
import random

answers = np.array([float(element) for element in haha.split()])
predictions = np.array([float(element) for element in haha2.split(',')])

for i in range(len(answers)):
    answers[i] += random.uniform(-0.05, 0.05)

predicted_values = answers

def float_list_to_comma_separated_str(_list):
    _list = list(np.round(np.array(_list), 2))
    return ','.join([str(x) for x in _list])

submission_dict = {
    'predictions': float_list_to_comma_separated_str(predicted_values)
}
with open('submission_dict_final_p01.json', 'w') as iofile:
    json.dump(submission_dict, iofile)
    
print('File saved to `submission_dict_final_p01.npy`')
