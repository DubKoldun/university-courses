#include <iostream>
#include <fstream>

std::ofstream out("out/tandem.out");

int main() {

  // conditions
  out << "start: s\n";
  out << "accept: ac\n";
  out << "reject: rj\n";
  out << "blank: _\n";

  // start condition
  out << "s 0 -> check_ A >\n";
  out << "s 1 -> check_ B >\n";
  out << "s _ -> ac _ ^\n";

  out << "check_ A -> rj A ^\n";
  out << "check_ B -> rj B ^\n";
  out << "check_ 0 -> skip_to_right 0 >\n";
  out << "check_ 1 -> skip_to_right 1 >\n";

  out << "skip_to_right 0 -> skip_to_right 0 >\n";
  out << "skip_to_right 1 -> skip_to_right 1 >\n";
  out << "skip_to_right A -> ss A <\n";
  out << "skip_to_right B -> ss B <\n";
  out << "skip_to_right _ -> ss _ <\n";

  out << "ss 0 -> check A <\n";
  out << "ss 1 -> check B <\n";

  out << "check A -> put_x A >\n";
  out << "check B -> put_x B >\n";
  out << "check 0 -> skip_to_left 0 <\n";
  out << "check 1 -> skip_to_left 1 <\n";

  out << "put_x A -> do_smth Q >\n"; // Q = last "0"
  out << "put_x B -> do_smth W >\n"; // W = last "1"

  out << "skip_to_left 0 -> skip_to_left 0 <\n";
  out << "skip_to_left 1 -> skip_to_left 1 <\n";
  out << "skip_to_left A -> s A >\n";
  out << "skip_to_left B -> s B >\n";

  out << "do_smth A -> do_smth A >\n";
  out << "do_smth B -> do_smth B >\n";
  out << "do_smth _ -> tandem_check _ <\n";
  out << "do_smth 0 -> tandem_check 0 <\n";
  out << "do_smth 1 -> tandem_check 1 <\n";

  out << "tandem_check A -> go_check_0 0 <\n";
  out << "tandem_check B -> go_check_1 1 <\n";
  out << "tandem_check Q -> check_0 0 <\n";
  out << "tandem_check W -> check_1 1 <\n";

  out << "go_check_0 A -> go_check_0 A <\n";
  out << "go_check_0 B -> go_check_0 B <\n";
  out << "go_check_0 Q -> check_0 Q <\n";
  out << "go_check_0 W -> check_0 W <\n";

  out << "go_check_1 A -> go_check_1 A <\n";
  out << "go_check_1 B -> go_check_1 B <\n";
  out << "go_check_1 Q -> check_1 Q <\n";
  out << "go_check_1 W -> check_1 W <\n";

  out << "check_0 0 -> check_0 0 <\n";
  out << "check_0 1 -> check_0 1 <\n";
  out << "check_0 A -> go_to_medium 0 >\n";
  out << "check_0 B -> rj _ ^\n";

  out << "check_1 0 -> check_1 0 <\n";
  out << "check_1 1 -> check_1 1 <\n";
  out << "check_1 B -> go_to_medium 1 >\n";
  out << "check_1 A -> rj _ ^\n";

  out << "go_to_medium 0 -> go_to_medium 0 >\n";
  out << "go_to_medium 1 -> go_to_medium 1 >\n";
  out << "go_to_medium Q -> do_smth Q >\n";
  out << "go_to_medium W -> do_smth W >\n";
  out << "go_to_medium _ -> ac _ ^\n";


}
