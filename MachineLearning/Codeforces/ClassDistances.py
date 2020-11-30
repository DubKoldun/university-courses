k = int(input())
n = int(input())

mass = [[] for i in range(k)]

for i in range(n):
    cur = input().split()
    mass[int(cur[1]) - 1].append(int(cur[0]))

ans1 = 0
ans2 = 0

for i in range(len(mass)):
    for j in range(len(mass)):
        size = len(mass[i])
        size2 = len(mass[j])

        if (i == j):
            for p in range(size):
                ans1 += abs(mass[i][p] - mass[j][size - 1 - p]) 
        else:
            for p in range(size):
                for q in range(size2):
                    ans2 += abs(mass[i][p] - mass[j][q])

print(ans1)
print(ans2)