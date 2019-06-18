module Grammar where

data Operation = Or | And | Impl

instance Show Operation where
  show Or   = "|"
  show And  = "&"
  show Impl = "->"

data Expr = Binary Operation Expr Expr
          | Not Expr
          | Var String

instance Show Expr where
  show (Binary op x y) = "(" ++ show op ++ "," ++ show x ++ "," ++ show y	 ++ ")"
  show (Not e)         = "(!" ++ show e ++ ")"
  show (Var name)      = name
