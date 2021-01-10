import random as rnd

def read_objs():
    n = int(input())
    ker_values = []
    ys = []

    for i in range(n):
        current_str = input().split()
        buff = [float(current_str[i]) for i in range(n)]
        
        ker_values.append(buff)
        ys.append(float(current_str[n]))

    res = float(input())

    return (ker_values, ys, res, n)

def smo(ker_values, classes, n, max_amount, reg_param):
    alpha = [0 for i in range(n)]
    threshold = 0
    amount = 0
    tol = 1e-5
    eps = 1e-15

    while amount < max_amount:
        am_changes_alpha = 0
    
        for i in range(n):
            e_i = threshold - classes[i]
            for z in range(n):
                e_i += alpha[z] * classes[z] * ker_values[z][i]
            
            buff = e_i * classes[i]
            
            if (buff < -tol and alpha[i] < reg_param) or (buff > tol and alpha[i] > 0):
                j = rnd.randrange(0, n)
                if j == i:
                    j += 1
                
                e_j = threshold - classes[j]
                for z in range(n):
                    e_j += alpha[z] * classes[z] * ker_values[z][j]
            
                old_alpha_i = alpha[i]
                old_alpha_j = alpha[j]
                L = 0.0
                H = 0.0

                if classes[i] == classes[j]:
                    L = max(0, alpha[i] + alpha[j] - reg_param)
                    H = min(reg_param, alpha[i] + alpha[j])
                else: 
                    L = max(0, alpha[j] - alpha[i])
                    H = min(reg_param, reg_param + alpha[j] - alpha[i])

                if (L == H):
                    continue

                eta = 2 * ker_values[i][j] - ker_values[i][i] - ker_values[j][j]
                if eta >= 0:
                    continue

                alpha[j] -= classes[j] * (e_i - e_j) / eta
                if (alpha[j] > H):
                    alpha[j] = H
                elif (alpha[j] < L):
                    alpha[j] = L
                else:
                    alpha[j] = alpha[j]

                if abs(alpha[j] - old_alpha_j) < eps:
                    continue

                alpha[i] = old_alpha_i + classes[i] * classes[j] * (old_alpha_j - alpha[j])
                b1 = threshold - e_i - classes[i]*(alpha[i] - old_alpha_i) * ker_values[i][i] - classes[j]*(alpha[j] - old_alpha_j) * ker_values[i][j]
                b2 = threshold - e_j - classes[j]*(alpha[j] - old_alpha_j) * ker_values[j][j] - classes[i]*(alpha[i] - old_alpha_i) * ker_values[i][j]

                if 0 < alpha[i] and alpha[i] < reg_param:
                    threshold = b1
                elif 0 < alpha[j] and alpha[j] < reg_param: 
                    threshold = b2
                else:
                    threshold = (b1 + b2) / 2.0

                am_changes_alpha += 1
        
        if am_changes_alpha == 0:
            amount += 1

    return alpha, threshold

vals, ys, c, n = read_objs()
vals, ys = vals, ys
mp = 5

alphas, b = smo(vals, ys, n, mp, c)

def print_():
    for alpha in alphas:
        print(0 if alpha < 0 else alpha)
    print(b)

print_()