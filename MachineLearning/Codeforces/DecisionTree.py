m, k, h = input().split()
m, k, h = int(m), int(k), int(h)

n = int(input())
objects = []
classes = []

for i in range(n):
    current_obj = input().split()
    classes.append(int(current_obj[m]))

    buff = []
    for j in range(m):
        buff.append(int(current_obj[j]))
    objects.append(buff)

print(objects, classes)
    
def gini_criterion(left, right):
    suma = sum(left) + sum(right)
    return 1 - sum([i / suma for i in left])

# def 
sum(1)

# if n < 1000:

    