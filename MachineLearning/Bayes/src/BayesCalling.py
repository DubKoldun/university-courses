from ctypes import *
from time import time
from random import choice

lib = cdll.LoadLibrary('/home/vutaliy/prod/university-courses/MachineLearning/Bayes/src/naiveBayes.so')

def naive_bayes(nth, file_from, file_to): 
    lib.NaiveBayes(c_int(nth), bytes(file_from, 'utf-8'), bytes(file_to, 'utf-8'))
    
def check(nth, file_to):
    lib.some2(c_int(nth), bytes(file_to, 'utf-8') )