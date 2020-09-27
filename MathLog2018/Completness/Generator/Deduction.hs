module Generator.Deduction (deductionToLeft, deductionToRight, aImpla) where

import DSrealization.Expression (Expr(..), DefExpr(..), ExprType(..))
import DSrealization.Hypothesises (checkHypothesises)
import DSrealization.Axioms (checkAxioms)

import Generator.Substitutions (substitution, defExpr, makeExpr)

import qualified Data.Map as Map (Map)

-- |- A -> A
-- A->A->A
-- A->(A->A)->A
-- (A->A->A)->(A->(A->A)->A)->(A->A)
-- (A->(A->A)->A)->(A->A)
-- A->A

aImpla :: Expr -> [DefExpr]
aImpla e = substitution e defExpr defExpr [
                                        DefExpr (Ax 1) (makeExpr "(A -> (A -> A))"),
                                        DefExpr (Ax 1) (makeExpr "(A -> ((A -> A) -> A))"),
                                        DefExpr (Ax 1) (makeExpr "((A -> (A -> A)) -> ((A -> ((A -> A) -> A)) -> (A -> A)))"),
                                        DefExpr (MP "(A -> (A -> A))" "((A -> (A -> A)) -> ((A -> ((A -> A) -> A)) -> (A -> A)))") (makeExpr "((A -> ((A -> A) -> A)) -> (A -> A))"),
                                        DefExpr (MP "(A -> ((A -> A) -> A))" "((A -> ((A -> A) -> A)) -> (A -> A))") (makeExpr "(A -> A)")
                                        ]

-- A == ax or hyp
-- A
-- A->B->A
-- B->A

axOrHyp :: ExprType -> Expr -> Expr -> [DefExpr]
axOrHyp type' e1 e2 = substitution e2 e1 defExpr [
                                                DefExpr type' (makeExpr "A"),
                                                DefExpr (Ax 1) (makeExpr "A->B->A"),
                                                DefExpr (MP "A" "A->B->A") (makeExpr "B->A")                                        
                                                ] 

modusPonens :: Expr -> DefExpr -> [DefExpr] -- sub to 4 variable?
modusPonens e1 e2 = substitution e1 from (_expr e2) [
                                              DefExpr (Ax 2) (makeExpr "(A->B)->(A->B->C)->(A->C)"),
                                              DefExpr (MP "(A->B)" "(A->B)->(A->B->C)->(A->C)") (makeExpr "(A->B->C)->(A->C)"),
                                              DefExpr (MP "(A->B->C)" "(A->B->C)->(A->C)") (makeExpr "(A->C)")                                       
                                              ]
                                              where from = makeExpr . _from . _type $ e2

-- G |- A->B => G, A |- B
deductionToLeft :: Expr -> Expr -> [DefExpr]
deductionToLeft e1 e2 = substitution e1 e2 defExpr [
                                                DefExpr (Hyp 1) (makeExpr "A"),
                                                DefExpr (MP "A" "(A -> B)") (makeExpr "B")                                                                
                                                ]

-- G, A |- B => G |- A->B 
deductionToRight :: Expr -> [DefExpr] -> [DefExpr]
deductionToRight e1 = concatMap (deduction e1) 

deduction :: Expr -> DefExpr -> [DefExpr]
deduction expr current  | expr == currentExpr = aImpla currentExpr
                        | otherwise = case type' of 
                            (MP _ _) -> modusPonens expr current
                            _        -> axOrHyp type' expr currentExpr
                        where 
                          currentExpr = _expr current
                          type' = _type current