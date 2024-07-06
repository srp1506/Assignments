#include <stdio.h>
#include <stdlib.h>
#include <time.h>
import random
import copy
import numpy as np

file_path = "trace3.txt"
arr = []


for i in range (256):
    arr.append("R: "+hex(random.randint(0,2**32-1)))  
    # Write data to the file
for i in range (32):
    arr.append("W: "+hex(random.randint(0,2**32-1)))  
arr=copy.copy(arr)*4
random.shuffle(arr)
with open(file_path, 'w') as file:
    for i in range (len(arr)):
        file.write(str(arr[i])+"\n")


