#include <iostream>
#include <cstdarg>


using std::string;

// Ноль
// Z: N_0 -> N_0, Z(x) = 0
int Z (int x) {
    return 0;
}

// Инкремент
// N: N_0 -> N_0, N(x) = x + 1
int N (int x) {
    return x + 1;
}

// Проекция
// U_i^n: N_0^n -> N_0, U_i^n(x1,...,x_n) = x_i
int U(int i) {
    throw string("Out of bound");
}

template<typename... T>
int U(int i, int x1, T... args) {
    if (i == 1) return x1;
    return U(i - 1, args...);
}

// Подстановка
// (f: N_0^n -> N_0) и (g_1,...g_n: N_0^m -> N_0), то (S{f,g_1,...,g_n}: N_0^m -> N_0). При этом (S{f,g_1,...,g_n}(x_1,...x_n) = f(g(x_1,...,x_n),...,g(x_1,...,x_n)))

// Рекурсия
// (f: N_0^n -> N_0) и (g: N_0^(n+2) -> N_0), то (R{f,g}: N_0^(n+1), при этом R{f,g}(x_1,...,x_n,y) = {f(x_1,...,x_n), y = 0 | g(x_1,...,x_n,y-1,R{f,g}(x_1,...,x_n,y-1))}


int main() {
    std::cout << U(2, 1, 2);

}
