#!/usr/bin/python3
import math
n = 21
# Your code should be below this line

# first check if the day "n" is in the month or 1 to 31
if (n > 0) and (n < 32):

    # day of the month divided by 7
    # the remainder is the day of the week
    # only the first and second 
    # day of the week are the weekend
    if (n%7 == 1) or (n%7 == 2):
        print("Weekdend")
    
    # every other day is a weekday 
    else:
        print("Weekday")

# day of the month "n" was not in range 1jan to 31jan
else:
    print("Not valid")










