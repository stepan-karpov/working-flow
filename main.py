import traceback
import sys
import os

def force_load(module_name):
    # f = open(module_name)
    f = open(module_name + ".py")
    lines = f.readlines()
    ldict = {}
    to_go = True
    while (to_go):
        try:
            cmd = ''.join(lines)
            exec(cmd, globals(), ldict)
            to_go = False
        except Exception as error:
            if (len(error.args) != 2):
                a, b, c = sys.exc_info()
                lines = lines[(c.tb_next).tb_lineno:]
            else:
                del lines[error.args[1][1] - 1]

    return ldict

# print(force_load("broken"))
# print(force_load("broken")['foo'])

# print("123")

# a = ExtendedList()
# a.append(1234)
# a.append(134)

# print(a.R)