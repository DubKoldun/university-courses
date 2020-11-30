from math import sqrt

n = int(input())

mass = [[int(x) for x in input().split()] for i in range(n)]
avg = [0, 0]
# print(avg)

for one in mass:
    avg[0] += one[0]
    avg[1] += one[1]

avg[0] /= n
avg[1] /= n

nom = denom = fst = snd = 0

for one in mass:
    buff1 = one[0] - avg[0]
    buff2 = one[1] - avg[1]
    nom += buff1 * buff2

    fst += buff1 ** 2
    snd += buff2 ** 2

denom = sqrt(fst * snd)

print(nom / denom if denom != 0 else 0)



