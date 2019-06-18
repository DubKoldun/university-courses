#include <iostream>
#include <fstream>


std::ofstream out("out/aplusb.out");

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
  out << "s _ -> minus _ <\n";

  out << "minus 1 -> skip_to_left 0 <\n";
  out << "minus 0 -> refactor 1 <\n";
  out << "minus + -> acc _ >\n";

  out << "refactor + -> delete + >\n";
  out << "refactor 0 -> refactor 1 <\n";
  out << "refactor 1 -> skip_to_left 0 <\n";

  out << "skip_to_left 0 -> skip_to_left 0 <\n";
  out << "skip_to_left 1 -> skip_to_left 1 <\n";
  out << "skip_to_left + -> plus + <\n";

  out << "plus 0 -> s 1 >\n";
  out << "plus 1 -> plus 0 <\n";
  out << "plus _ -> s 1 >\n";

  out << "delete _ -> end_of _ <\n";
  out << "delete 0 -> delete _ >\n";
  out << "delete 1 -> delete _ >\n";

  out << "end_of _ -> end_of _ <\n";
  out << "end_of + -> acc _ <\n";

  out << "acc 1 -> acc 1 <\n";
  out << "acc 0 -> acc 0 <\n";
  out << "acc _ -> ac _ >\n";


}



/*

  // conditions
  out << "start: s\n";
  out << "accept: ac\n";
  out << "reject: rj\n";
  out << "blank: _\n";

  // start condition
  out << "s + -> s + >\n";
  out << "s 0 -> s 0 >\n";
  out << "s 1 -> s 1 >\n";
  out << "s _ -> skip_to_left = <\n";

  out << "skip_to_left + -> plus + <\n";
  out << "skip_to_left 0 -> skip_to_left 0 <\n";
  out << "skip_to_left 1 -> skip_to_left 1 <\n";
  out << "skip_to_left x -> skip_to_left x <\n";
  out << "skip_to_left A -> skip_to_left A <\n";
  out << "skip_to_left B -> skip_to_left B <\n";
  out << "skip_to_left = -> skip_to_left = <\n";
  out << "skip_to_left _ -> end _ >\n";

  out << "plus _ -> end _ >\n";
  out << "plus x -> plus x <\n";
  out << "plus 0 -> skip_to_right0 x >\n";
  out << "plus 1 -> skip_to_right1 x >\n";

  out << "skip_to_right0 x -> skip_to_right0 x >\n";
  out << "skip_to_right0 0 -> skip_to_right0 0 >\n";
  out << "skip_to_right0 1 -> skip_to_right0 1 >\n";
  out << "skip_to_right0 + -> skip0 + >\n";

  out << "skip_to_right1 x -> skip_to_right1 x >\n";
  out << "skip_to_right1 0 -> skip_to_right1 0 >\n";
  out << "skip_to_right1 1 -> skip_to_right1 1 >\n";
  out << "skip_to_right1 + -> skip1 + >\n";

  out << "skip0 = -> plus0 = <\n";
  out << "skip0 x -> plus0 x <\n";
  out << "skip0 1 -> skip0 1 >\n";
  out << "skip0 0 -> skip0 0 >\n";

  out << "skip1 = -> plus1 = <\n";
  out << "skip1 x -> plus1 x <\n";
  out << "skip1 1 -> skip1 1 >\n";
  out << "skip1 0 -> skip1 0 >\n";

  out << "plus0 0 -> write0 x >\n";
  out << "plus0 1 -> write1 x >\n";
  out << "plus0 + -> write0 + >\n";

  out << "plus1 0 -> write1 x >\n";
  out << "plus1 1 -> write2 x >\n";
  out << "plus1 + -> write1 + >\n";

  out << "write0 x -> write0 x >\n";
  out << "write0 = -> write0 = >\n";
  out << "write0 A -> write0 A >\n";
  out << "write0 B -> write0 B >\n";
  out << "write0 0 -> skip_to_left A <\n";
  out << "write0 1 -> skip_to_left B <\n";
  out << "write0 _ -> skip_to_left A <\n";

  out << "write1 x -> write1 x >\n";
  out << "write1 = -> write1 = >\n";
  out << "write1 A -> write1 A >\n";
  out << "write1 B -> write1 B >\n";
  out << "write1 0 -> skip_to_left B <\n";
  out << "write1 1 -> put1 A >\n";
  out << "write1 _ -> skip_to_left B <\n";

  out << "put1 _ -> skip_to_left 1 <\n";

  out << "write2 x -> write2 x >\n";
  out << "write2 = -> write2 = >\n";
  out << "write2 A -> write2 A >\n";
  out << "write2 B -> write2 B >\n";
  out << "write2 0 -> put1 A <\n";
  out << "write2 1 -> put1 B >\n";
  out << "write2 _ -> put1 A <\n";

  out << "end x -> end _ >\n";
  out << "end + -> end _ >\n";
  out << "end 1 -> do_empty 1 >\n";
  out << "end = -> reverse x >\n";

  out << "do_empty 1 -> do_empty 1 >\n";
  out << "do_empty 0 -> do_empty 0 >\n";
  out << "do_empty x -> plus_ x <\n";

  out << "plus_ 1 -> write1_ x >\n";
  out << "plus_ 0 -> write0_ x >\n";

  out << "write0_ x -> write0_ x >\n";
  out << "write0_ = -> write0_ = >\n";
  out << "write0_ A -> write0_ A >\n";
  out << "write0_ B -> write0_ B >\n";
  out << "write0_ 0 -> skip_to_left A <\n";
  out << "write0_ 1 -> skip_to_left B <\n";
  out << "write0_ _ -> skip_to_left A <\n";

  out << "write1_ x -> write1_ x >\n";
  out << "write1_ = -> write1_ = >\n";
  out << "write1_ A -> write1_ A >\n";
  out << "write1_ B -> write1_ B >\n";
  out << "write1_ 0 -> skip_to_left B <\n";
  out << "write1_ 1 -> put1_ A >\n";
  out << "write1_ _ -> skip_to_left B <\n";

  out << "put1_ _ -> skip_to_left 1 <\n";

  out << "reverse A -> save0 x <\n";
  out << "reverse B -> save1 x <\n";
  out << "reverse 1 -> save1 x <\n";
  out << "reverse x -> reverse x >\n";
  out << "reverse _ -> end_of _ <\n";

  out << "end_of x -> end_of _ <\n";
  out << "end_of 1 -> end_of 1 <\n";
  out << "end_of 0 -> end_of 0 <\n";
  out << "end_of _ -> ac _ >\n";

  out << "save0 1 -> save0 1 <\n";
  out << "save0 0 -> save0 0 <\n";
  out << "save0 x -> save0 x <\n";
  out << "save0 _ -> end_skip 0 >\n";

  out << "save1 1 -> save1 1 <\n";
  out << "save1 0 -> save1 0 <\n";
  out << "save1 x -> save1 x <\n";
  out << "save1 _ -> end_skip 1 >\n";

  out << "end_skip 1 -> end_skip 1 >\n";
  out << "end_skip 0 -> end_skip 0 >\n";
  out << "end_skip x -> reverse x ^\n";*/
