#include <iostream>
#include <fstream>

std::ofstream out("out/reverse.out");

int main() {
  // conditions
  out << "start: s\n";
  out << "accept: ac\n";
  out << "reject: rj\n";
  out << "blank: _\n";

  // start condition
  out << "s + -> s + >\n";
  out << "s 0 -> s 0 >\n";
  out << "s 1 -> s 1 >\n";
  out << "s _ -> reverse _ <\n";

  out << "reverse 1 -> reverse1 B >\n";
  out << "reverse 0 -> reverse0 A >\n";
  out << "reverse A -> reverse A <\n";
  out << "reverse B -> reverse B <\n";
  out << "reverse _ -> end _ >\n";

  out << "reverse0 A -> reverse0 A >\n";
  out << "reverse0 B -> reverse0 B >\n";
  out << "reverse0 1 -> reverse0 1 >\n";
  out << "reverse0 0 -> reverse0 0 >\n";
  out << "reverse0 _ -> skip_to_eq 0 <\n";

  out << "reverse1 A -> reverse1 A >\n";
  out << "reverse1 B -> reverse1 B >\n";
  out << "reverse1 1 -> reverse1 1 >\n";
  out << "reverse1 0 -> reverse1 0 >\n";
  out << "reverse1 _ -> skip_to_eq 1 <\n";

  out << "skip_to_eq 1 -> skip_to_eq 1 <\n";
  out << "skip_to_eq 0 -> skip_to_eq 0 <\n";
  out << "skip_to_eq A -> reverse A <\n";
  out << "skip_to_eq B -> reverse B <\n";

  out << "end A -> end _ >\n";
  out << "end B -> end _ >\n";
  out << "end 1 -> ac 1 ^\n";
  out << "end 0 -> ac 0 ^\n";

}
