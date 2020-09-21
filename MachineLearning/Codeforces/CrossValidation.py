n, m, k = input().split()
classElements = input().split()

k = int(k)
m = int(m)

dic = {}
for i in range(m):
    dic['{0}'.format(i+1)] = []

count = 0

for x in classElements:
    dic[x].append(classElements.index(x, count) + 1)
    count += 1
    
ans = {}
for i in range(k):
    ans[i] = []

count = 0

for x in dic: 
    for item in dic[x]:
        ans[count].append(item)
        count += 1
        count %= k

for x in ans:
    print(len(ans[x]), *ans[x], sep=" ")            
