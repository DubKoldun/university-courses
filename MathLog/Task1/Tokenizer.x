{
module Tokenizer where
}

%wrapper "basic"

$digit = 0-9
$alpha = [A-Z]
$apostrophe = [']

:-

  $white+                    ;
  \(                         { \x -> LeftBr }
  \)                         { \x -> RightBr }
  \|                         { \x -> OrXY }
  "&"                        { \x -> AndXY }
  "->"                       { \x -> Implication }
  "!"                        { \x -> NotXY }
  $alpha [ $alpha $digit $apostrophe ]*    { \s -> Variable s }

{

data Token = AndXY
           | OrXY
           | Implication
           | NotXY
           | LeftBr
           | RightBr
           | Variable String

instance Show Token where
  show (AndXY) = "&"
  show (Variable s) = s
  show (OrXY) = "|"
  show (LeftBr) = "("
  show (RightBr) = ")"
  show (Implication) = "->"
  show (NotXY) = "!"
}
