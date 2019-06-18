#include <iostream>
#include <fstream>

std::ofstream out("out/convertto2.out");

int main() {
  // conditions
  out << "start: s\n";
  out << "accept: ac\n";
  out << "reject: rj\n";
  out << "blank: _\n";

  // start condition
  out << "s 0 -> eq 0 <\n";
  out << "s 1 -> eq 1 <\n";
  out << "s 2 -> eq 2 <\n";

  out << "eq _ -> set_0 = <\n";
  out << "set_0 _ -> go_to_end 0 >\n";

  out << "go_to_end 0 -> go_to_end 0 >\n";
  out << "go_to_end 1 -> go_to_end 1 >\n";
  out << "go_to_end 2 -> go_to_end 2 >\n";
  out << "go_to_end = -> go_to_end = >\n";
  out << "go_to_end _ -> minus _ <\n";

  out << "minus 2 -> go_to_eq 1 <\n";
  out << "minus 1 -> go_to_eq 0 <\n";
  out << "minus 0 -> refactor 2 <\n";

  out << "refactor 0 -> refactor 2 <\n";
  out << "refactor 1 -> go_to_eq 0 <\n";
  out << "refactor 2 -> go_to_eq 1 <\n";
  out << "refactor = -> delete = >\n";

  out << "go_to_eq 0 -> go_to_eq 0 <\n";
  out << "go_to_eq 1 -> go_to_eq 1 <\n";
  out << "go_to_eq 2 -> go_to_eq 2 <\n";
  out << "go_to_eq = -> plus = <\n";

  out << "plus _ -> go_to_end 1 >\n";
  out << "plus 0 -> go_to_end 1 >\n";
  out << "plus 1 -> plus 0 <\n";

  out << "delete _ -> end_of _ <\n";
  out << "delete 0 -> delete _ >\n";
  out << "delete 1 -> delete _ >\n";
  out << "delete 2 -> delete _ >\n";

  out << "end_of _ -> end_of _ <\n";
  out << "end_of = -> acc _ <\n";

  out << "acc 1 -> acc 1 <\n";
  out << "acc 0 -> acc 0 <\n";
  out << "acc _ -> ac _ >\n";

}
