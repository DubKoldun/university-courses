#include <fstream>

std::ofstream out("out/multiplication.out");

int main() {
  // conditions
  out << "start: s_\n";
  out << "accept: ac\n";
  out << "reject: rj\n";
  out << "blank: _\n";

//rewrite on plus
  out << "s_ 0 -> s_ 0 >\n";
  out << "s_ 1 -> s_ 1 >\n";
  out << "s_ * -> s_ * >\n";
  out << "s_ + -> s_ + >\n";
  out << "s_ _ -> go_ _ <\n";

  out << "go_ 0 -> go_ 1 <\n";
  out << "go_ 1 -> go_to_first_number_ 0 <\n";
  out << "go_ * -> delete * >\n";

  out << "go_to_first_number_ 0 -> go_to_first_number_ 0 <\n";
  out << "go_to_first_number_ 1 -> go_to_first_number_ 1 <\n";
  out << "go_to_first_number_ * -> go_to_first_number_ * <\n";
  out << "go_to_first_number_ + -> read_ + >\n";
  out << "go_to_first_number_ _ -> read_ + >\n";

  out << "read_ 0 -> read_ 0 >\n";
  out << "read_ 1 -> read_ 1 >\n";
  out << "read_ A -> new_ 0 <\n";
  out << "read_ B -> new_ 1 <\n";
  out << "read_ * -> new_ * <\n";

  out << "new_ 0 -> write0_ A <\n";
  out << "new_ 1 -> write1_ B <\n";
  out << "new_ + -> minus + <\n"; //s_

  out << "write0_ 0 -> write0_ 0 <\n";
  out << "write0_ 1 -> write0_ 1 <\n";
  out << "write0_ + -> write0_ + <\n";
  out << "write0_ x -> skip_plus_ 0 >\n";
  out << "write0_ _ -> skip_plus_ 0 >\n";

  out << "write1_ 0 -> write1_ 0 <\n";
  out << "write1_ 1 -> write1_ 1 <\n";
  out << "write1_ + -> write1_ + <\n";
  out << "write1_ x -> skip_plus_ 1 >\n";
  out << "write1_ _ -> skip_plus_ 1 >\n";

  out << "skip_plus_ 0 -> skip_plus_ 0 >\n";
  out << "skip_plus_ 1 -> skip_plus_ 1 >\n";
  out << "skip_plus_ + -> read_ + >\n";

  out << "minus 0 -> minus 1 <\n";
  out << "minus 1 -> go_to_left 0 <\n";
  out << "minus _ -> zero _ >\n";
  out << "minus = -> clear = >\n";

  out << "clear 0 -> clear x >\n";
  out << "clear 1 -> clear x >\n";
  out << "clear + -> s_ + >\n";

  out << "go_to_left 0 -> go_to_left 0 <\n";
  out << "go_to_left 1 -> go_to_left 1 <\n";
  out << "go_to_left _ -> plus = <\n";
  out << "go_to_left = -> plus = <\n";

  out << "plus _ -> go_to_right 1 >\n";
  out << "plus 0 -> go_to_right 1 >\n";
  out << "plus 1 -> plus 0 <\n";

  out << "go_to_right = -> go_to_right = >\n";
  out << "go_to_right 0 -> go_to_right 0 >\n";
  out << "go_to_right 1 -> go_to_right 1 >\n";
  out << "go_to_right + -> minus + <\n";

  out << "zero 0 -> zero _ >\n";
  out << "zero 1 -> zero _ >\n";
  out << "zero + -> zero _ >\n";
  out << "zero * -> zero _ >\n";
  out << "zero _ -> ac 0 ^\n";

  out << "delete 0 -> delete 0 >\n";
  out << "delete 1 -> delete 1 >\n";
  out << "delete _ -> acc _ <\n";

  out << "acc 0 -> acc _ <\n";
  out << "acc 1 -> acc _ <\n";
  out << "acc * -> acc _ <\n";
  out << "acc + -> acc _ <\n";
  out << "acc = -> not_zero _ <\n";
  out << "acc x -> acc _ <\n";
  out << "acc _ -> zero _ ^\n";

  out << "not_zero 0 -> not_zero 0 <\n";
  out << "not_zero 1 -> not_zero 1 <\n";
  out << "not_zero _ -> ac _ >\n";

}
