module Main where

import Data.Maybe (fromJust)
import qualified Data.Map as Map (Map, empty, fromList, toList, insert, (!?)) 

import Parser.Analyzer (alexScanTokens)
import Parser.LineParser (parseFirstLine)
import DSrealization.Expression (Expr(..), DefExpr(..), ExprType(..))
import DSrealization.Hypothesises
import Algo.Minimize (checker)
import Algo.Recovery (recovery)


toHA :: String -> IO HypotAndAns
toHA = return . parseFirstLine . alexScanTokens 

first' :: (t1, t2) -> t1
first' (x,y) = x 

second' :: (t1, t2) -> t2
second' (x,y) = y

--мб обернуть в монаду? )
printList :: [(Int, DefExpr)] -> Map.Map Int Int -> Int -> IO ()
printList []     indexes i = return ()
printList (x:xs) indexes i  = do 
    let expr = snd x 
    case expr of 
        DefExpr d _ (MP from to) e -> putStrLn . show $ DefExpr d i (MP (fromJust $ indexes Map.!? to) (fromJust $ indexes Map.!? from)) (_expr expr)
        DefExpr d _ t e            -> putStrLn . show $ DefExpr d i t e
    printList xs (Map.insert (_numStr expr) i indexes) (i+1) 

printLog x = print . second' . first' $ first' x

main :: IO ()
main = do
    input <- getLine
    ha <- toHA input
    x <- checker (_answer ha) (Map.fromList $ zip (_hypothesises ha) [1..]) Map.empty Map.empty
    -- printLog x
    if (_numStr . first' . first' $ first' x) == -1 
    then putStrLn "Proof is incorrect" 
    else do 
        y <- recovery (second' $ first' x) (first' . first' $ first' x)
        let lst = Map.toList . snd $ y 
        putStrLn . show $ ha 
        printList lst Map.empty 1

    -- putStr $ show $ snd y

    -- putStr "\n"
    -- print . first' . first' $ first' x
    -- putStr "\n"
    -- print . second' . first' $ first' x
    -- putStr "\n"
    -- print . second' $ first' x
    -- putStr "\n"
    -- print $ second' x

    return ()