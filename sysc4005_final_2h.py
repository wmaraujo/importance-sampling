#! /usr/bin/env python3

from random import normalvariate
from math import exp, sqrt

n = 155000000
total = 0
sumVar = 0
print("Simulation begins now")
for i in range(n):
    X = normalvariate(8, 1)
    if (X > 8):
        total += exp(32-8*X)
        sumVar += exp(64-16*X)
mean = total / n
variance = (sumVar - (total**2) / n) / (n - 1)

print("The estimated value is:", mean)
print("The variance is:", variance)
print("95% CI: {", mean - 1.96*sqrt(variance / n), ",", \
                   mean + 1.96*sqrt(variance / n), "}")
