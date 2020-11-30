from math import sqrt

n = int(input())
lst1 = []
lst2 = []
buff1 = []
buff2 = []

for i in range(n):
    cur = input().split()
    lst1.append(int(cur[0]))
    lst2.append(int(cur[1]))
    buff1.append(int(cur[0]))
    buff2.append(int(cur[1]))

lst1.sort()
lst2.sort()

ans = 0
for i in range(n):
    ans += (lst1.index(buff1[i]) - lst2.index(buff2[i])) ** 2

print(1 - 6 / n / (n-1) / (n+1) * ans) 