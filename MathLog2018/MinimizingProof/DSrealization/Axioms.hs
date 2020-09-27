module DSrealization.Axioms (checkAxioms) where

import Control.Monad (liftM, ap)

import Control.Monad.Cont
import Control.Monad.Trans (lift)
import Control.Monad.Trans.Reader (runReaderT, ask, asks, ReaderT(..))

import Parser.Parser (parseExpression)
import Parser.Analyzer (alexScanTokens)
import DSrealization.Expression (Expr(..), Operation(..))

--Baybe for new Eq realization
data Baybe a = Some a | None

instance (Eq a) => Eq (Baybe a) where 
    Some x == Some y = x == y
    None == _ = False
    _ == None = False

instance Functor Baybe where
    fmap = liftM

instance Applicative Baybe where
    pure = return
    (<*>) = ap

instance Monad Baybe where 
    return = Some
    Some m >>= k = k m
    None >>= _ = None 

getLeftImpl :: Expr -> Baybe Expr
getLeftImpl (Binary Impl l _) = Some l
getLeftImpl _                 = None

getRightImpl :: Expr -> Baybe Expr
getRightImpl (Binary Impl _ r) = Some r
getRightImpl _                 = None

getLeftOr :: Expr -> Baybe Expr
getLeftOr (Binary Or l _) = Some l
getLeftOr _                 = None

getRightOr :: Expr -> Baybe Expr
getRightOr (Binary Or _ r) = Some r
getRightOr _                 = None

getLeftAnd :: Expr -> Baybe Expr
getLeftAnd (Binary And l _) = Some l
getLeftAnd _                 = None

getRightAnd :: Expr -> Baybe Expr
getRightAnd (Binary And _ r) = Some r
getRightAnd _                 = None

getNeg :: Expr -> Baybe Expr
getNeg (Not e) = Some e
getNeg _       = None

--checkAxN

--  "A->B->A"
checkAx1 :: Expr  -> Bool 
checkAx1 expr = l == rr where
    l = getLeftImpl expr
    rr = getRightImpl expr >>= getRightImpl

-- "(A->B)->(A->B->C)->(A->C)"
checkAx2 :: Expr -> Bool
checkAx2 expr = ll   == rll  && ll == rrl && -- A
                lr   == rlrl &&              -- B
                rlrr == rrr                  -- C 
                where 
                    l = getLeftImpl expr
                    r = getRightImpl expr
                    ll = l >>= getLeftImpl
                    rr = r >>= getRightImpl 
                    rl = r >>= getLeftImpl
                    lr = l >>= getRightImpl
                    rll = rl >>= getLeftImpl
                    rrl = rr >>= getLeftImpl
                    rlr = rl >>= getRightImpl
                    rlrl = rlr >>= getLeftImpl
                    rlrr = rlr >>= getRightImpl
                    rrr = rr >>= getRightImpl

--"A->B->A&B"
checkAx3 :: Expr -> Bool
checkAx3 expr = l == la && rl == ra where 
    l = getLeftImpl expr
    a = getRightImpl expr >>= getRightImpl
    la = a >>= getLeftAnd
    rl = getRightImpl expr >>= getLeftImpl
    ra = a >>= getRightAnd

--"A&B->A"
checkAx4 :: Expr -> Bool
checkAx4 expr = la == r where
    la = getLeftImpl expr >>= getLeftAnd
    r = getRightImpl expr


-- "A&B->B"
checkAx5 :: Expr -> Bool
checkAx5 expr = ra == r where
    ra = getLeftImpl expr >>= getRightAnd
    r = getRightImpl expr

-- "A->A|B"
checkAx6 :: Expr -> Bool
checkAx6 expr = l == lo where 
    l = getLeftImpl expr 
    lo = getRightImpl expr >>= getLeftOr

-- "B->A|B",
checkAx7 :: Expr -> Bool
checkAx7 expr = l == ro where 
    l = getLeftImpl expr 
    ro = getRightImpl expr >>= getRightOr

--"(A->C)->(B->C)->(A|B->C)"
checkAx8 :: Expr -> Bool              
checkAx8 expr = lr  == rlr   && lr == rrr &&  --C
                ll  == rrllo &&               --A
                rll == rrlro                  --B
                where
                    l = getLeftImpl expr
                    r = getRightImpl expr
                    ll = l >>= getLeftImpl 
                    lr = l >>= getRightImpl 
                    rr = r >>= getRightImpl
                    rl = r >>= getLeftImpl
                    rll = rl >>= getLeftImpl
                    rlr = rl >>= getRightImpl 
                    rrr = rr >>= getRightImpl
                    rrllo = rr >>= getLeftImpl >>= getLeftOr
                    rrlro = rr >>= getLeftImpl >>= getRightOr

--"(A->B)->(A->!B)->!A"
checkAx9 :: Expr -> Bool
checkAx9 expr = ll == rll && ll == rrn && --A
                lr == rlrn               --B
                where
                    l = getLeftImpl expr
                    r = getRightImpl expr
                    ll = l >>= getLeftImpl
                    lr = l >>= getRightImpl
                    rl = r >>= getLeftImpl
                    rll = rl >>= getLeftImpl
                    rrn = r >>= getRightImpl >>= getNeg
                    rlrn = rl >>= getRightImpl >>= getNeg

--"!!A->A"
checkAx10 :: Expr -> Bool
checkAx10 expr = lnn == r where 
    r = getRightImpl expr 
    lnn = getLeftImpl expr >>= getNeg >>= getNeg 


--checker
checkAxioms' :: Expr -> Cont Int Int
checkAxioms' expr = do
    cont $ \c -> if checkAx1 expr then 1 else c ()
    cont $ \c -> if checkAx2 expr then 2 else c ()
    cont $ \c -> if checkAx3 expr then 3 else c ()
    cont $ \c -> if checkAx4 expr then 4 else c ()
    cont $ \c -> if checkAx5 expr then 5 else c ()
    cont $ \c -> if checkAx6 expr then 6 else c ()
    cont $ \c -> if checkAx7 expr then 7 else c ()
    cont $ \c -> if checkAx8 expr then 8 else c ()
    cont $ \c -> if checkAx9 expr then 9 else c ()
    cont $ \c -> if checkAx10 expr then 10 else c ()
    return 0

checkAxioms :: Expr -> Int
checkAxioms expr = runCont (checkAxioms' expr) id


axioms :: [Expr]
axioms = map (parseExpression . alexScanTokens) [
                                                "A->B->A",
                                                "(A->B)->(A->B->C)->(A->C)",
                                                "A->B->A&B",
                                                "A&B->A",
                                                "A&B->B",
                                                "A->A|B",
                                                "B->A|B",
                                                "(A->C)->(B->C)->(A|B->C)",
                                                "(A->B)->(A->!B)->!A",
                                                "!!A->A"
                                                ]
-- map checkAxioms axioms