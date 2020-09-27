module DSrealization.Hypothesises where

import Data.Maybe

import DSrealization.Expression

import qualified Data.Map as Map (Map, (!?)) 

-- grammar for hypothesises and answer

data HypotAndAns = HypotAndAns {
                                 _hypothesises :: [Expr],
                                 _answer       ::  Expr
                               }

instance Show HypotAndAns where
    show (HypotAndAns hypothesises answer) = conclusionHyp hypothesises ++ "|- " ++ show answer
        where conclusionHyp :: [Expr] -> String
              conclusionHyp []     = "";
              conclusionHyp [x]    = show x ++ " "
              conclusionHyp (x:xs) = show x ++ ", " ++ conclusionHyp xs

checkHypothesises :: Expr -> Map.Map Expr Int -> Int
checkHypothesises expr ha = Data.Maybe.fromMaybe 0 (ha Map.!? expr)