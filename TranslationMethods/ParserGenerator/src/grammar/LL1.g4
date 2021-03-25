grammar LL1;

start : tokens_ rules_;

tokens_ : TOKENS COLON NEXTLINE (TAB token_ NEXTLINE)+ TAB SEMICOLON
        ;

rules_ : RULES COLON NEXTLINE (TAB rule_ NEXTLINE)+ TAB SEMICOLON
       ;

token_ : NAME COLON regexp
       ;

regexp : STRING #FString
       | buff+ #FBuff
       ;

buff : CBRACKETL? SBRACKETL reg+ SBTACKETR (CBRACKETR MODIFIER)?
     ;

reg : SMALLLETTERS #SmallLetters
    | BIGLETTERS #BigLetters
    | DIGITS #Digits
    ;

rule_ : NAME RIGHTARROW STRING; // need to add attributes and correct parsing rules

TOKENS : 'tokens';
RULES : 'rules';
RIGHTARROW : '->';
COMMON : ',';
COLON : ':';
TAB : '\t';
NEXTLINE : '\n';
SEMICOLON : ';';
STRING : '\''~[\t\n\r']+'\'';
NAME : [a-zA-Z_]([a-zA-Z0-9_'])*;
MODIFIER : [*+?];
SBRACKETL : '[';
SBTACKETR : ']';
CBRACKETL : '(';
CBRACKETR : ')';
SMALLLETTERS : 'a-z';
BIGLETTERS : 'A-Z';
DIGITS : '0-9';


//LITERAL : [0-9]+;
//LAND: '&&';
//LOR : '||';
//OPERATION : ([%^&*,\-+/]);
//PREDICATE : ([<>]+|'=='|'!='|'<='|'>=');
//EQUALS : '=';
//SPACES : [ \t\r]+ -> channel(HIDDEN);
//IF : 'if';
//TRUE: 'true';
//FALSE: 'false';
//PRINT: 'print';
