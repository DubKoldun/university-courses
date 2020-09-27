{
module Parser.Parser where

import DSrealization.Expression
import Parser.Analyzer
}

%name      parseExpression
%tokentype { Token }
%error     { parseError }

%token VAR  { Variable_ $$ }
%token IMPL   { Implication }
%token OR     { Or_ }
%token AND    { And_ }
%token NOT    { Not_ }
%token LEFTBR  { LeftBr }
%token RIGHTBR { RightBr }
%token NEXT { NextLine }

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
parseError :: [Token] -> a
parseError e = error $ "Parse error " ++ (show e)
}
