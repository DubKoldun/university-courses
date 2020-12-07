

def read_objs():
    n = int(input())
    ker_values = []
    ys = []

    for i in range(n):
        current_str = input().split()
        buff = [float(current_str[i]) for i in range(len(current_str) - 1)]
        ker_values.append(buff)
        ys.append(float(current_str[n]))

    res = float(input())

    return (ker_values, ys)

ker_values, ys = read_objs()

print(ker_values, ys)
