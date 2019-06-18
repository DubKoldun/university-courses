#include <iostream>
#include <fstream>

std::ifstream in ("rps2.in");
std::ofstream out("rps2.out");

int main() {
    int a, b, c, q, w, e;
    in >> a >> b >> c;
    in >> q >> w >> e;
    q -= std::min(a,q); a -= std::min(a,q); // neutral ahahahahahahahahah
    q -= std::min(q,b); b -= std::min(q,b); // won
    w -= std::min(b,w); b -= std::min(w,b); // neutral
    w -= std::min(c,w); c -= std::min(w,c); // won
    e -= std::min(c,e); c -= std::min(e,c); // neutral
    e -= std::min(e,a); a -= std::min(e,a); // won
    out << a+b+c;
    return 0;
}