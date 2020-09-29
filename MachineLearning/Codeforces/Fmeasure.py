
n = int(input())
matrix = [[int(j) for j in input().split()] for i in range(n)]

def transposition(m):
    for i in range(n):
        for j in range(0,i):
            m[i][j] ^= m[j][i]
            m[j][i] ^= m[i][j]
            m[i][j] ^= m[j][i]

transposition(matrix)

def row(i):
    ans = 0
    for j in range(n):
        ans += matrix[j][i]
    return ans

def col(i):
    ans = 0
    for j in range(n):
        ans += matrix[i][j] 
    return ans

def all_():
    ans = 0
    for row in matrix:
        for item in row:
            ans += item
    return ans

alll = all_()

def prec_i(i):
    ans = 0
    for j in range(n):
        ans += matrix[j][i]
    if (ans == 0): return 1
    return matrix[i][i] / ans 

def recall_i(i):
    ans = 0
    for j in range(n):
        ans += matrix[i][j]
    if (ans == 0): return 1
    return matrix[i][i] / ans

def f_beta(i, beta):
    recall = recall_i(i)
    precision = prec_i(i)
    weight = pow(beta,2)
    denominator = (weight * precision + recall)
    if (denominator == 0): return 0
    return (1 + weight) * precision * recall / denominator

def f_micro(beta):
    ans = 0
    for i in range(n):
        ans += row(i) * f_beta(i, beta)
    return ans / alll 

def prec_w():
    ans = 0
    for i in range(n):
        col_ = col(i)
        if (col_ != 0):
            ans += matrix[i][i] * row(i) / col(i)
    return ans / alll

def recall_w():
    ans = 0
    for i in range(n):
        ans += matrix[i][i]
    return ans / alll

def f_macro(beta):
    precision = prec_w()
    recall = recall_w()
    weight = pow(beta,2)
    return (1 + weight) * precision * recall / (weight * precision + recall)

print(round(f_macro(1),6))
print(round(f_micro(1),6))