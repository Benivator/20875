#!/usr/bin/python3
import math
number = 100
# Your code should be below this line

# if number is in the fibbinichi sequence
if (number > 0) and ((number % 2) == 0) and (((5*(number**2) + 4)**0.5)%1 == 0):
    print("Yes")


else:
    print("no")




