module DSrealization.Expression where

import Data.Hashable
import Data.HashSet (HashSet)
import qualified Data.HashSet as Set

-- grammar for expression

data Operation = Or | And | Impl deriving (Eq, Ord)

data Expr = Binary { op :: Operation, left :: Expr, right :: Expr }
          | Not Expr
          | Var String
          deriving (Eq, Ord)


-- instance show

instance Show Operation where
    show Or   = " | "
    show And  = " & "
    show Impl = " -> "

instance Show Expr where
    show (Binary op x y) = "(" ++ show x ++ show op ++ show y ++ ")"
    show (Not e)         = "!" ++ show e
    show (Var name)      = name

-- instance Hashable

instance Hashable Operation where
    hashWithSalt salt Or = hashWithSalt salt (show Or)
    hashWithSalt salt And = hashWithSalt salt (show And)
    hashWithSalt salt Impl = hashWithSalt salt (show Impl)

instance Hashable Expr where
    hashWithSalt salt (Binary op x y) = (salt `hashWithSalt` op) +
                                        ((20::Int) `hashWithSalt` x) +
                                        ((30::Int) `hashWithSalt` y)
    hashWithSalt salt (Not e)         = salt `hashWithSalt`
                                        (1::Int) `hashWithSalt` e
    hashWithSalt salt (Var name)      = salt `hashWithSalt` name

data ExprType = Ax { _num :: Int } | MP { _from :: String, _to :: String } | Hyp { _num :: Int }

instance Show ExprType where
    show (Ax n) = "Ax. sch. " ++ show n
    show (Hyp n) = "Hypothesis " ++ show n
    show (MP f s) = "M.P. " ++ show f ++ ", " ++ show s

data DefExpr = DefExpr {
                        _type   :: ExprType, 
                        _expr   :: Expr
                        }

instance Show DefExpr where 
    show (DefExpr t e) = show t ++ " " ++ show e -- for testing
    -- show (DefExpr _ e) = show e
    