{
module Parsenizer where

import Grammar
import Tokenizer
}

%name      parsing
%tokentype { Token }
%error { errorParse }

%token VAR  { Variable $$ }
%token IMPL   { Implication }
%token OR     { OrXY }
%token AND    { AndXY }
%token NOT    { NotXY }
%token LEFTBR  { LeftBr }
%token RIGHTBR { RightBr }

%%

Expr
  : Disj               { $1 }
  | Disj IMPL Expr     { Binary Impl $1 $3 }

Disj
  : Conj               { $1 }
  | Disj OR Conj       { Binary Or $1 $3 }

Conj
  : Not                { $1 }
  | Conj AND Not       { Binary And $1 $3 }

Not
  : NOT Not               { Not $2 }
  | LEFTBR Expr RIGHTBR   { $2 }
  | Term                  { $1 }

Term
  : VAR            { Var $1 }

{
errorParse = fail "error while parsing"
}
