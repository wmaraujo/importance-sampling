#! /usr/bin/env python3

"""
Importance sampling simulation to find the probability
of a standard normal random variable exceeding 8
P(X > 8), where X is distributed according to the standard normal distribution.

True value is about 6.22096057410^-16
Obtained with WolframAlpha:
http://www.wolframalpha.com/input/?i=1+-+CDF[NormalDistribution[0%2C+1]%2C+8]
Note, it is required to press "more digits" on the WolframAlpha page to
get better accuracy and precession.
"""

from random import normalvariate
from math import exp, sqrt

__author__ = "Wesley Araujo"
__license__ = "Creative Commons Attribution 4.0"
"http://creativecommons.org/licenses/by/4.0/"

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
