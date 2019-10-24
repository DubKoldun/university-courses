#include <iostream>
#include <fstream>

std::ofstream out ("out/balanced.out");

int main() {
  // conditions
  out << "start: s\n";
  out << "accept: ac\n";
  out << "reject: rj\n";
  out << "blank: _\n";

  // start condition
  out << "s _ -> ac _ ^\n";
  out << "s x -> s _ >\n";
  out << "s ( -> right ( >\n";
  out << "s ) -> rj ) ^\n";

  out << "right ( -> right ( >\n";
  out << "right ) -> left x <\n";
  out << "right x -> right x >\n";
  out << "right _ -> rj _ ^\n";

  out << "left ( -> to_start x <\n";
  out << "left x -> left x <\n";

  out << "to_start ( -> to_start ( <\n";
  out << "to_start ) -> to_start ) <\n";
  out << "to_start x -> to_start x <\n";
  out << "to_start _ -> s _ >\n";

}
