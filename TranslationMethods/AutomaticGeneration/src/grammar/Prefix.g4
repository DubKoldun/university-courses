grammar Prefix;

start : (block+);

block : assignment
      | function
      | expression
      ;

assignment : EQUALS NAME expression
           ;

function : IFF bool BEGIN start END (BEGIN start END)? #IfCall
         | PRINTF expression #PrintCall
         | WHILE bool BEGIN start END #WhileCall
         ;

expression : arith
           | bool
           ;

arith : ARITH_OP arith arith #ArithCall
      | NAME #NameCall
      | NUMBER #NumberCall
      ;

bool : PREDICATE arith arith #PredicateCall
     | LOGICAL_OP bool bool #LogicalCall
     | boolConst #BoolConstCall
     ;

boolConst : TRUE
          | FALSE
          ;


END : 'end';
BEGIN : 'begin';
WHILE : 'while';
IFF : 'if';
TRUE: 'true';
FALSE: 'false';
PRINTF: 'print';
ELSE : 'else';
LOGICAL_OP : '&&'|'^'|'||';
ARITH_OP : '%'|'^'|'*'|'-'|'+';
PREDICATE : '<'|'>'|'=='|'!='|'<='|'>=';
EQUALS : '=';
NUMBER : [1-9][0-9]*;
NAME : [a-zA-Z_]([a-zA-Z0-9_'])*;
SPACES : [ \t\r]+ -> skip;
