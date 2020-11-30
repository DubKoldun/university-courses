import random as rnd
from math import sqrt


# file = open("/home/vutaliy/Downloads/LR/0.40_0.65.txt", "r") 
# n, m = file.readline().split()
n, m = input().split()
n, m = int(n), int(m)

objects = []
main_attribute = []

min_max_obj = [[float("inf"), float("-inf")] for i in range(m) ]

for i in range(n):
    
    # inpt = file.readline().split()
    inpt = input().split()
    buff = []
    
    main_attribute.append(float(inpt[m]))

    for j in range(len(inpt) - 1):
        x = float(inpt[j])
        buff.append(x)

        if (x < min_max_obj[j][0]):
            min_max_obj[j][0] = x

        if (x > min_max_obj[j][1]):
            min_max_obj[j][1] = x
    
    objects.append(buff)
blabla = 1
# if (n == 2):
#     print(31.0)
#     print(-60420.0)
# elif (n == 4):
#     print(2.0)
#     print(-1.0)
# else:
if blabla == 1:
    old_objects = [i.copy() for i in objects]

    def min_max(objs, mins_and_maxs): 
        for i in range(len(objs)):
            for j in range(len(objs[0])):
                objs[i][j] = (objs[i][j] - mins_and_maxs[j][0]) / (mins_and_maxs[j][1] - mins_and_maxs[j][0]) if mins_and_maxs[j][1] - mins_and_maxs[j][0] != 0 else 0

    min_max(objects, min_max_obj)

    def add_ones(objs):
        for i in range(len(objs)):
            objs[i].append(1)

    add_ones(objects)
    add_ones(old_objects)

    def sign(vec):
        buff = []
        for obj in vec:
            if (obj < 0):
                buff.append(-1) 
            elif (obj > 0):
                buff.append(1)
            else:
                buff.append(0)
        return buff

    def multiply_vec(vec1, vec2):
        buff = []
        for i in range(len(vec1)):
            buff.append(vec1[i] * vec2[i])
        return sum(buff)

    def multiply_s_vec(x, vec):
        buff = []
        for i in vec:
            buff.append(x * i)
        return buff

    def dif_sq(x, w, y):
        # print(x, w)
        buff = multiply_vec(x, w)
        # print(buff)
        return multiply_s_vec(multiply_vec(x, w) - y, x)

    def suma(lst):
        buff = [0] * len(lst[0])
        for obj in lst:
            for i in range(len(obj)):
                buff[i] += obj[i]
        return buff

    def empirical_risk(w, func, start, k):
        for i in range(start, start + k + 1):
            buff = func(objects[i], w, main_attribute[i])

        lst = [func(objects[i], w, main_attribute[i]) for i in range(start, start + k + 1)]
        # print(lst)
        return multiply_s_vec(1 / k, suma(lst))

    def diff(vec1, vec2):
        buff = []
        for i in range(len(vec1)):
            buff.append(vec1[i] - vec2[i])
        return buff

    def add(vec1, vec2):
        buff = []
        for i in range(len(vec1)):
            buff.append(vec1[i] + vec2[i])
        return buff

    ## algo

    amount = 2000

    def bgd(amount, batch_size = sqrt(n), h = 0.05, lmbd2 = 0.1):
        lmbd = 0.01
        start = rnd.randint(0, len(objects) - batch_size - 1)

        # weights = [rnd.uniform(-1/(2 * m+1), 1/(2 * m+1)) for i in range(m+1)]
        weights = [0 for i in range(m+1)]
        
        assessment = add(empirical_risk(weights, dif_sq, start, batch_size), multiply_s_vec(lmbd2, sign(weights)))


        for i in range(1, amount): 
            start = rnd.randint(0, len(objects) - batch_size - 1)
            
            buff = multiply_s_vec(h, assessment)
            weights = diff(weights, buff)

            keks =  add(empirical_risk(weights, dif_sq, start, batch_size), multiply_s_vec(lmbd2, sign(weights)))
            assessment = add(multiply_s_vec((1 - lmbd), assessment), multiply_s_vec(lmbd, keks))

        return weights

    def denormalize(ans):
        sumAns = 0

        for i in range(len(ans)-1):
            ans[i] /= (min_max_obj[i][1] - min_max_obj[i][0]) if min_max_obj[i][1] - min_max_obj[i][0] != 0 else 1
            sumAns = sumAns + ans[i] * min_max_obj[i][0]

        ans[len(ans)-1] -= sumAns 

    def nmrse(preds_y, ans_y):
        sum_ = 0
        min_p = min(preds_y)
        max_p = max(preds_y)
        for ix, pred in enumerate(preds_y):
            sum_ += (pred - ans_y[ix]) ** 2
        return ((sum_ / len(preds_y)) ** 0.5) / (max_p - min_p) 

    # batch_size = min(2,int(sqrt(m)))
    # ans = bgd(amount, batch_size)
    # denormalize(ans)
    # pred = [multiply_vec(ans, old_objects[i]) for i in range(len(objects))]
    # print(nmrse(pred, main_attribute))

    def find_best_reg():
        regs = []
        scores = []
        for lmbd in range(0,3):
            ans = bgd(amount, batch_size = min(2,int(sqrt(m))), lmbd2 = 1)
            denormalize(ans)
            regs.append(ans)
            y_pred = [multiply_vec(ans, old_objects[i]) for i in range(len(objects))]
            scores.append(nmrse(y_pred, main_attribute))
        # print(scores)
        return regs[scores.index(min(scores))]

    best_reg = find_best_reg()

    for i in best_reg:
        print(i)

    # print(best_reg)
    # best_reg2 = find_best_reg()
    # print(best_reg2)
