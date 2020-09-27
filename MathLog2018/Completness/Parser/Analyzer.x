{
module Parser.Analyzer where
}

%wrapper "basic"

$digit = 0-9
$alpha = [A-Z]
$spaces = [\ \t \r]
$apostrophe = [']

:-
  $spaces                    ;
  "|-"                       { \x -> Perp }
  \(                         { \x -> LeftBr }
  \)                         { \x -> RightBr }
  \|                         { \x -> Or_ }
  \n                         { \x -> NextLine }
  ","                        { \x -> Comma }
  "&"                        { \x -> And_ }
  "->"                       { \x -> Implication }
  "!"                        { \x -> Not_ }
  $alpha [ $alpha $digit $apostrophe ]*    { \x -> Variable_ x }

{
data Token = And_
           | Or_
           | Implication
           | Not_
           | LeftBr
           | RightBr
           | Variable_ String
           | Perp
           | Comma
           | NextLine
           deriving (Show, Eq)
}
