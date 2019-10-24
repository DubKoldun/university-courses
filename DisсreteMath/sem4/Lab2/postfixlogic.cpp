#include <fstream>

std::ofstream out("out/postfixlogic.out");

int main() {
  out << "2\n";
  out << "S 1 _ -> S _ > 1 >\n";
  out << "S 0 _ -> S _ > 0 >\n";
  out << "S o _ -> OR _ ^ _ <\n";
  out << "S a _ -> AND _ ^ _ <\n";
  out << "S _ _ -> END _ ^ _ <\n";

  out << "OR _ 0 -> OR0 _ ^ _ <\n";
  out << "OR _ 1 -> OR1 _ ^ _ <\n";
  out << "OR0 _ 0 -> S _ > 0 >\n";
  out << "OR0 _ 1 -> S _ > 1 >\n";
  out << "OR1 _ 0 -> S _ > 1 >\n";
  out << "OR1 _ 1 -> S _ > 1 >\n";

  out << "AND _ 0 -> AND0 _ ^ _ <\n";
  out << "AND _ 1 -> AND1 _ ^ _ <\n";
  out << "AND0 _ 0 -> S _ > 0 >\n";
  out << "AND0 _ 1 -> S _ > 0 >\n";
  out << "AND1 _ 0 -> S _ > 0 >\n";
  out << "AND1 _ 1 -> S _ > 1 >\n";

  out << "END _ 0 -> AC 0 ^ _ <\n";
  out << "END _ 1 -> AC 1 ^ _ <\n";

}
