module Generator.Substitutions (substitution, substitutionToOneStr, defExpr, makeExpr) where 

import Parser.Analyzer (alexScanTokens)
import Parser.Parser (parseExpression)
import DSrealization.Expression (Expr(..), DefExpr(..), ExprType(..))

--without monad implementation

ts :: Expr -> String 
ts = show

makeExpr :: String -> Expr 
makeExpr = parseExpression . alexScanTokens

defExpr :: Expr
defExpr = makeExpr "Z'''"

substitutionToOneSym :: Expr -> Expr -> Expr -> Char -> String
substitutionToOneSym e _ _ 'A' = ts e 
substitutionToOneSym _ e _ 'B' = ts e
substitutionToOneSym _ _ e 'C' = ts e
substitutionToOneSym _ _ _ c      = [c]

substitutionToOneStr :: Expr -> Expr -> Expr -> String -> String
substitutionToOneStr e1 e2 e3 = concatMap (substitutionToOneSym e1 e2 e3)

substitutionToAllExpr :: Expr -> Expr -> Expr -> [Expr] -> [Expr] 
substitutionToAllExpr e1 e2 e3 = map (makeExpr . substitutionToOneStr e1 e2 e3 . show)

makeDef :: Expr -> Expr -> Expr -> ExprType -> Expr -> DefExpr
makeDef e1 e2 e3 (MP str1 str2) e = DefExpr (MP (substitutionToOneStr e1 e2 e3 str1) (substitutionToOneStr e1 e2 e3 str2)) e
makeDef e1 e2 e3 type'          e = DefExpr type' e

substitution :: Expr -> Expr -> Expr -> [DefExpr] -> [DefExpr]
substitution e1 e2 e3 proof = zipWith (makeDef e1 e2 e3) types (substitutionToAllExpr e1 e2 e3 exprs)
    where types = map _type proof 
          exprs = map _expr proof