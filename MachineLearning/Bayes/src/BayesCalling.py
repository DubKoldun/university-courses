from ctypes import *
from time import time
from random import choice

lib = cdll.LoadLibrary('/home/vutaliy/prod/university-courses/MachineLearning/Bayes/src/naiveBayes.so')

def naive_bayes(nth, file_from, file_to, leg, spam, smooth): 
    lib.NaiveBayes(c_int(nth), bytes(file_from, 'utf-8'), bytes(file_to, 'utf-8'), c_longdouble(leg), c_longdouble(spam), c_longdouble(smooth))
    
def check(nth, file_to):
    lib.some2(c_int(nth), bytes(file_to, 'utf-8'))


# file_from = "/home/vutaliy/prod/university-courses/MachineLearning/Bayes/test/test1"
# file_to = "/home/vutaliy/prod/university-courses/MachineLearning/Bayes/ans0"
# naive_bayes(1, file_from, file_to, 0.1, 0.1, 1e-5)