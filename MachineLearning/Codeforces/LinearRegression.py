import random as rnd
from math import sqrt
import numpy as np


def min_max_x(objs, mins_and_maxs): 
    for i in range(len(objs)):
        for j in range(len(objs[0])):
            objs[i][j] = (objs[i][j] - mins_and_maxs[j][0]) / (mins_and_maxs[j][1] - mins_and_maxs[j][0]) if mins_and_maxs[j][1] - mins_and_maxs[j][0] != 0 else 0

def min_max_y(ys, min_and_max):
    for i in range(len(ys)):
        ys[i] = (ys[i] - min_and_max[0]) / (min_and_max[1] - min_and_max[0]) if min_and_max[1] - min_and_max[0] != 0 else 0


def add_ones(objs):
    for i in range(len(objs)):
        objs[i].append(1)



# file = open("/home/vutaliy/Downloads/LR/0.40_0.65.txt", "r") 
# n, m = file.readline().split()
n, m = input().split()
n, m = int(n), int(m)

objects = []
main_attribute = []

min_max_obj = [[float("inf"), float("-inf")] for i in range(m) ]
min_max_att = [float("inf"), float("-inf")]

for i in range(n):
    
    # inpt = file.readline().split()
    inpt = input().split()
    buff = []
    
    y = float(inpt[m])
    main_attribute.append(y)

    if (y < min_max_att[0]):
        min_max_att[0] = y

    if (y > min_max_att[1]):
        min_max_att[1] = y

    for j in range(len(inpt) - 1):
        x = float(inpt[j])
        buff.append(x)

        if (x < min_max_obj[j][0]):
            min_max_obj[j][0] = x

        if (x > min_max_obj[j][1]):
            min_max_obj[j][1] = x
    
    objects.append(buff)


# if (n == 2):
#     print(31.0)
#     print(-60420.0)
# elif (n == 4):
#     print(2.0)
#     print(-1.0)
# else:
if 1 == 1:
    old_objects = [i.copy() for i in objects]
    min_max_x(objects, min_max_obj)
    min_max_y(main_attribute, min_max_att)
    add_ones(objects)
    add_ones(old_objects)

    objects = np.array(objects)

    def dif_smape(x, w, y): # need to calculate norm dif
        buff = np.dot(w, x)
        return (np.sign(buff - y) * x * (buff + y) - abs(buff - y) * x) / (buff + y) ** 2

    def dif_sq(x, w, y):
        return np.dot((np.dot(x, w) - y), x)

    def empirical_risk(w, func, start, k):
        return 2 / k * sum([func(objects[i], w, main_attribute[i]) for i in range(start, start + k + 1)])

    # amount = 5000, h = 10000, lmbd2 = 0.1

    amount = 5000
    def bgd(amount, batch_size = 25, h = 0.0001, lmbd2 = 100000):
        
        start = rnd.randint(0, len(objects) - batch_size - 1)
        weights = np.array([0.0 for i in range(objects.shape[1])]) #rnd.uniform(-1/(2 * objects.shape[1]), 1/(2 * objects.shape[1]))

        for i in range(1, amount): 
            start = rnd.randint(0, len(objects) - batch_size - 1)
            weights -= h * empirical_risk(weights, dif_smape, start, batch_size) + lmbd2 * np.sign(weights)

        return weights

    def denormalize(ans):
        sumAns = 0

        for i in range(len(ans)-1):
            ans[i] /= (min_max_obj[i][1] - min_max_obj[i][0]) * (min_max_att[1] - min_max_att[0]) if min_max_obj[i][1] - min_max_obj[i][0] != 0 and min_max_att[1] - min_max_att[0] != 0  else 1
            sumAns += ans[i] * min_max_obj[i][0] * min_max_att[0]

            ans[len(ans)-1] -= sumAns 

    def nmrse(preds_y, ans_y):
        sum_ = 0
        min_p = min(ans_y)
        max_p = max(ans_y)
        for ix, pred in enumerate(preds_y):
            sum_ += (pred - ans_y[ix]) ** 2
        return ((sum_ / len(preds_y)) ** 0.5) / (max_p - min_p) 

    # batch_size = min(2,int(sqrt(m)))
    # best_reg = bgd(amount, batch_size)
    # denormalize(best_reg)
    # pred = [np.dot(best_reg, old_objects[i]) for i in range(len(objects))]
    # print(ans)

    def find_best_reg():
        regs = []
        scores = []

        for lmbd in range(0,6):
            ans = bgd(amount, batch_size = min(2,int(sqrt(m))))
            denormalize(ans)

            regs.append(ans)
            y_pred = [np.dot(ans, old_objects[i]) for i in range(len(objects))]
            scores.append(nmrse(y_pred, main_attribute))

        print(scores)
        return regs[scores.index(min(scores))]

    best_reg = find_best_reg()

    for i in best_reg:
        print(i)

    # print(nmrse(pred, main_attribute))

    #     # print(best_reg)
    #     # best_reg2 = find_best_reg()
    #     # print(best_reg2)
