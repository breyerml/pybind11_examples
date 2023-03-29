import numpy as np

import showcase

#
# simple
#
print("\nsimple:")

res = showcase.add(1.5, 1.5)
print(res)

res = showcase.py_add(1, 1)
print(res)
# help(showcase.py_add)

#
# overloads
#
print("\noverloads:")

res = showcase.mult(1.5, 1.5)
print(res)
res = showcase.mult(2, 2)
print(res)

#
# templates
#
print("\ntemplates:")

res = showcase.div(3.0, 1.5)
print(res)
res = showcase.div(3, 2)
print(res)

#
# stl
#
print("\nstl:")

res = showcase.dot([1, 2, 3], [4, 5, 6])
print(res)
res = showcase.dot(np.asarray([1, 2, 3]), np.asarray([4, 5, 6]))
print(res)

res = showcase.concat("Hello", "World")
print(res)

showcase.print(res)

#
# args
#
print("\nstl:")

res = showcase.saxpy(2, [1, 2, 3], [4, 5, 6])
print(res)

res = showcase.saxpy([1, 2, 3], [4, 5, 6])  # a is default 1.0
print(res)

res = showcase.saxpy([1, 2, 3], [4, 5, 6], a=10)
print(res)
