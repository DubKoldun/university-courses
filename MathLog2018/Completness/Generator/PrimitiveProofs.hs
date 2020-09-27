module Generator.PrimitiveProofs where 

import DSrealization.Expression (Expr(..), DefExpr(..), ExprType(..))

import Generator.Substitutions (substitution, substitutionToOneStr, defExpr, makeExpr)
import Generator.Deduction (deductionToRight, aImpla)

checker :: [DefExpr] -> IO ()
checker [x] = print x
checker (x:xs) = do { print x; checker xs }


-- A,B |- A->B
-- B->A->B
-- B
-- A->B

aImplb :: Expr -> Expr -> [DefExpr]
aImplb e1 e2 = substitution e1 e2 defExpr [
                                        DefExpr (Ax 1) (makeExpr "(B -> (A -> B))"),
                                        DefExpr (Hyp 2) (makeExpr "B"),
                                        DefExpr (MP "B" "(B -> (A -> B))") (makeExpr "(A -> B)")   
                                        ]

naImplb :: Expr -> Expr -> [DefExpr]
naImplb = aImplb 

-- A, !B |- A->B
-- !B
-- !B->A->!B
-- A->!B
-- (A->!B)->(A->B)->(A->!B)
-- (A->B)->(A->!B)
-- (A->B)->(A->!B)->!A
-- ((A->B)->(A->!B))->((A->B)->(A->!B)->!A)->((A->B)->!A)
-- ((A->B)->(A->!B)->!A)->((A->B)->!A)
-- ((A->B)->!A)
-- A
-- A->(A->B)->A
-- (A->B)->A
-- ((A->B)->A)->((A->B)->!A)->!(A->B)
-- ((A->B)->!A)->!(A->B)
-- !(A->B)

aImplnb :: Expr -> Expr -> [DefExpr]
aImplnb e1 e2 = substitution e1 e2 defExpr [
                                        DefExpr (Hyp 2) (makeExpr "!B"),
                                        DefExpr (Ax 1) (makeExpr "!B->A->!B"),
                                        DefExpr (MP "!B" "!B->A->!B") (makeExpr "A->!B"),
                                        DefExpr (Ax 1) (makeExpr "(A->!B)->(A->B)->(A->!B)"),
                                        DefExpr (MP "A->!B" "(A->!B)->(A->B)->(A->!B)") (makeExpr "(A->B)->(A->!B)"),
                                        DefExpr (Ax 9) (makeExpr "(A->B)->(A->!B)->!A"),
                                        DefExpr (Ax 2) (makeExpr "((A->B)->(A->!B))->((A->B)->(A->!B)->!A)->((A->B)->!A)"),
                                        DefExpr (MP "(A->B)->(A->!B)" "((A->B)->(A->!B))->((A->B)->(A->!B)->!A)->((A->B)->!A)") (makeExpr "((A->B)->(A->!B)->!A)->((A->B)->!A)"),
                                        DefExpr (MP "(A->B)->(A->!B)->!A" "((A->B)->(A->!B)->!A)->((A->B)->!A)") (makeExpr "((A->B)->!A)"),
                                        DefExpr (Hyp 1) (makeExpr "A"),
                                        DefExpr (Ax 1) (makeExpr "A->(A->B)->A"),
                                        DefExpr (MP "A" "A->(A->B)->A") (makeExpr "(A->B)->A"),
                                        DefExpr (Ax 9) (makeExpr "((A->B)->A)->((A->B)->!A)->!(A->B)"),
                                        DefExpr (MP "(A->B)->A" "((A->B)->A)->((A->B)->!A)->!(A->B)") (makeExpr "((A->B)->!A)->!(A->B)"),
                                        DefExpr (MP "((A->B)->!A)" "((A->B)->!A)->!(A->B)") (makeExpr "!(A->B)")
                                        ]

-- !A, !B |- A->B <=> !A, !B, A |- B
-- A 
-- A->!B->A
-- !B->A
-- !A
-- !A->!B->!A
-- !B->!A
-- (!B->A)->(!B->!A)->!!B
-- (!B->!A)->!!B
-- !!B
-- !!B->B
-- B

naImplnb :: Expr -> Expr -> [DefExpr]
naImplnb e1 e2 = deductionToRight e1 (substitution e1 e2 defExpr [
                            DefExpr (Hyp 3) (makeExpr "A"), 
                            DefExpr (Ax 1) (makeExpr "A->!B->A"),
                            DefExpr (MP "A" "A->!B->A") (makeExpr "!B->A"),
                            DefExpr (Hyp 1) (makeExpr "!A"),
                            DefExpr (Ax 1) (makeExpr "!A->!B->!A"),
                            DefExpr (MP "!A" "!A->!B->!A") (makeExpr "!B->!A"),
                            DefExpr (Ax 9) (makeExpr "(!B->A)->(!B->!A)->!!B"),
                            DefExpr (MP "!B->A" "(!B->A)->(!B->!A)->!!B") (makeExpr "(!B->!A)->!!B"),
                            DefExpr (MP "!B->!A" "(!B->!A)->!!B") (makeExpr "!!B"),
                            DefExpr (Ax 10) (makeExpr "!!B->B"),
                            DefExpr (MP "!!B" "!!B->B") (makeExpr "B")
                            ] )


-- A,B |- A&B
-- A
-- B
-- A -> B -> A&B
-- B -> A&B
-- A&B

aAndb :: Expr -> Expr -> [DefExpr]
aAndb e1 e2 = substitution e1 e2 defExpr [
                                        DefExpr (Hyp 1) (makeExpr "A"),
                                        DefExpr (Hyp 2) (makeExpr "B"),
                                        DefExpr (Ax 3) (makeExpr "A->B->A&B"),
                                        DefExpr (MP "A" "A->B->A&B") (makeExpr "B->A&B"),
                                        DefExpr (MP "B" "B->A&B") (makeExpr "A&B")
                                        ]

-- !A,B|-!A&B
-- !A->A&B->!A
-- !A
-- A&B->!A
-- A&B->A
-- (A&B->A)->(A&B->!A)->!A&B
-- (A&B->!A)->!A&B
-- !(A&B)

naAndb :: Expr -> Expr -> [DefExpr]
naAndb e1 e2 = substitution e1 e2 defExpr [
                                        DefExpr (Hyp 1) (makeExpr "!A"),
                                        DefExpr (Ax 1) (makeExpr "!A->A&B->!A"),
                                        DefExpr (MP "!A" "!A->A&B->!A") (makeExpr "A&B->!A"),
                                        DefExpr (Ax 4) (makeExpr "A&B->A"),
                                        DefExpr (Ax 9) (makeExpr "(A&B->A)->(A&B->!A)->!A&B"),
                                        DefExpr (MP "A&B->A" "(A&B->A)->(A&B->!A)->!A&B") (makeExpr "(A&B->!A)->!A&B"),
                                        DefExpr (MP "A&B->!A" "(A&B->!A)->!A&B") (makeExpr "!(A&B)")
                                        ]

naAndnb :: Expr -> Expr -> [DefExpr]
naAndnb = naAndb

-- A,!B|- !(A&B)
-- !B->A&B->!B
-- !B
-- A&B->!B
-- A&B->B
-- (A&B->B)->(A&B->!B)->!A&B
-- (A&B->!B)->!A&B
-- !(A&B)

aAndnb :: Expr -> Expr -> [DefExpr]
aAndnb e1 e2 = substitution e1 e2 defExpr [
                                        DefExpr (Hyp 2) (makeExpr "!B"),
                                        DefExpr (Ax 1) (makeExpr "!B->A&B->!B"),
                                        DefExpr (MP "!B" "!B->A&B->!B") (makeExpr "A&B->!B"),
                                        DefExpr (Ax 5) (makeExpr "A&B->B"),
                                        DefExpr (Ax 9) (makeExpr "(A&B->B)->(A&B->!B)->!(A&B)"),
                                        DefExpr (MP "A&B->B" "(A&B->B)->(A&B->!B)->!(A&B)") (makeExpr "(A&B->!B)->!(A&B)"),
                                        DefExpr (MP "A&B->!B" "(A&B->!B)->!(A&B)") (makeExpr "!(A&B)")
                                        ]

-- A,B |- A|B
-- A
-- A->A|B
-- A|B

aOrb :: Expr -> Expr -> [DefExpr]
aOrb e1 e2 = substitution e1 e2 defExpr [
                                        DefExpr (Hyp 1) (makeExpr "A"),
                                        DefExpr (Ax 6) (makeExpr "A->A|B"),
                                        DefExpr (MP "A" "A->A|B") (makeExpr "A|B")
                                        ]

aOrnb :: Expr -> Expr -> [DefExpr]
aOrnb = aOrb

-- !A,B |- A|B
-- B
-- B->A|B
-- A|B

naOrb :: Expr -> Expr -> [DefExpr]
naOrb e1 e2 = substitution e1 e2 defExpr [
                                        DefExpr (Hyp 1) (makeExpr "B"),
                                        DefExpr (Ax 7) (makeExpr "B->A|B"),
                                        DefExpr (MP "B" "B->A|B") (makeExpr "A|B")
                                        ]

-- !A,!B|- !(A|B)
-- A->B
-- B->B
-- (A->B)->(B->B)->(A|B->B)
-- (B->B)->(A|B->B)
-- (A|B->B)
-- !B
-- !B->A|B->!B
-- A|B->!B
-- (A|B->B)->(A|B->!B)->!(A|B)
-- (A|B->!B)->!(A|B)
-- !(A|B)

naOrnb :: Expr -> Expr -> [DefExpr]
naOrnb e1 e2 = naAndnb e1 e2 ++ aImpla e2 ++
    substitution e1 e2 defExpr [
                            DefExpr (Ax 8) (makeExpr "(A->B)->(B->B)->(A|B->B)"),
                            DefExpr (MP "A->B" "(A->B)->(B->B)->(A|B->B)") (makeExpr "(B->B)->(A|B->B)"),
                            DefExpr (MP "B->B" "(B->B)->(A|B->B)") (makeExpr "(A|B->B)"),
                            DefExpr (Hyp 2) (makeExpr "!B"),
                            DefExpr (Ax 1) (makeExpr "!B->A|B->!B"),
                            DefExpr (MP "!B" "!B->A|B->!B") (makeExpr "A|B->!B"),
                            DefExpr (Ax 9) (makeExpr "(A|B->B)->(A|B->!B)->!(A|B)"),
                            DefExpr (MP "(A|B->B)" "(A|B->B)->(A|B->!B)->!(A|B)") (makeExpr "(A|B->!B)->!(A|B)"),
                            DefExpr (MP "A|B->!B" "(A|B->!B)->!(A|B)") (makeExpr "!(A|B)")
                            ]

-- |-(A->B)->!B->!A <=> A->B,!B|-!A
-- !B->A->!B
-- !B
-- A->!B
-- A->B
-- (A->B)->(A->!B)->!A
-- (A->!B)->!A
-- !A

contraposition :: Expr -> [DefExpr]
contraposition e1 = deductionToRight e1 (deductionToRight (Not (right e1)) (substitution (left e1) (right e1) defExpr [
    DefExpr (Hyp 2) (makeExpr "!B"),
    DefExpr (Ax 1) (makeExpr "!B->A->!B"),
    DefExpr (MP "!B" "!B->A->!B") (makeExpr "A->!B"),
    DefExpr (Hyp 1) (makeExpr "A->B"),
    DefExpr (Ax 9) (makeExpr "(A->B)->(A->!B)->!A"),
    DefExpr (MP "A->B" "(A->B)->(A->!B)->!A") (makeExpr "(A->!B)->!A"),
    DefExpr (MP "A->!B" "(A->!B)->!A") (makeExpr "!A")
    ]))

-- |- A|!A
-- A->A|!A
-- (A->A|!A)->(!(A|!A)->!A)
-- (!(A|!A)->!A)
-- !A->A|!A
-- (!A->A|!A)->(!(A|!A)->!!A)
-- (!(A|!A)->!!A)
-- (!(A|!A)->!A)->(!(A|!A)->!!A)->!!(A|!A)
-- (!(A|!A)->!!A)->!!(A|!A)
-- !!(A|!A)
-- !!(A|!A)->A|!A
-- A|!A

excludedThirdRule :: Expr -> [DefExpr]
excludedThirdRule e1 = 
    substitution e1 defExpr defExpr [DefExpr (Ax 6) (makeExpr "A->A|!A")] ++ 
    contraposition (makeExpr $ substitutionToOneStr e1 defExpr defExpr "(A->A|!A)") ++
    substitution e1 defExpr defExpr [DefExpr (MP "A->A|!A" "(A->A|!A)->(!(A|!A)->!A)") (makeExpr "(!(A|!A)->!A)"), DefExpr (Ax 7) (makeExpr "!A->A|!A")] 
    ++ contraposition (makeExpr $ substitutionToOneStr e1 defExpr defExpr "(!A->A|!A)") ++
    substitution e1 defExpr defExpr [
        DefExpr (MP "!A->A|!A" "(!A->A|!A)->(!(A|!A)->!!A)") (makeExpr "(!(A|!A)->!!A)"),
        DefExpr (Ax 9) (makeExpr "(!(A|!A)->!A)->(!(A|!A)->!!A)->!!(A|!A)"),
        DefExpr (MP "(!(A|!A)->!A)" "(!(A|!A)->!A)->(!(A|!A)->!!A)->!!(A|!A)") (makeExpr "(!(A|!A)->!!A)->!!(A|!A)"),
        DefExpr (MP "(!(A|!A)->!!A)" "(!(A|!A)->!!A)->!!(A|!A)") (makeExpr "!!(A|!A)"),
        DefExpr (Ax 10) (makeExpr "!!(A|!A)->A|!A"),
        DefExpr (MP "!!(A|!A)" "!!(A|!A)->A|!A") (makeExpr "A|!A")
    ]

-- G,A|-B , G,!A|-B => G|-B
-- G|-A->B
-- G|-!A->B
-- A|!A
-- (A->B)->(!A->B)->(A|!A->B)
-- (!A->B)->(A|!A->B)
-- (A|!A->B)
-- B

exclusionOfAssumption :: Expr -> [DefExpr] -> [DefExpr] -> [DefExpr]
exclusionOfAssumption e1 proof1 proof2 = deductionToRight e1 proof1 ++ deductionToRight (Not e1) proof2 ++ excludedThirdRule e1 ++
    substitution e1 defExpr defExpr [
        DefExpr (Ax 8) (makeExpr "(A->B)->(!A->B)->(A|!A->B)"),
        DefExpr (MP "A->B" "(A->B)->(!A->B)->(A|!A->B)") (makeExpr "(!A->B)->(A|!A->B)"),
        DefExpr (MP "!A->B" "(!A->B)->(A|!A->B)") (makeExpr "(A|!A->B)"),
        DefExpr (MP "A|!A" "(A|!A->B)") (makeExpr "B")
    ]
