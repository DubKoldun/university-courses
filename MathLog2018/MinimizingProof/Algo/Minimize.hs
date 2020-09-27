module Algo.Minimize (checker) where

import Data.Maybe
import Data.Functor.Identity

import System.IO (isEOF)
import Control.Monad
import Control.Monad.Trans (lift)
import Control.Monad.Trans.Writer (WriterT(..), tell)
import Control.Monad.Trans.Reader (ReaderT(..), asks)
import Control.Monad.Trans.State (StateT(..), get, put, modify)

import qualified Data.Map as Map (Map, member, (!?), insertWith)
-- import qualified Data.HashMap as Map (HashMap, member, (!?), insertWith)

import Parser.Parser (parseExpression)
import Parser.Analyzer (alexScanTokens)
import DSrealization.Expression (ExprType(..), Expr(..), DefExpr(..), Operation(..)) 
import DSrealization.Axioms     (checkAxioms)
import DSrealization.Hypothesises (checkHypothesises)

type Hypothesises = Map.Map Expr Int
type ProvedMap    = Map.Map Expr DefExpr 
type MPMap        = Map.Map Expr [DefExpr] 
-- type MPMap     = Map.HashMap Expr [Expr] 

false' :: Expr -> DefExpr
false' = DefExpr 0 (-1) (Ax (-1)) 

toE :: String -> Expr
toE = parseExpression . alexScanTokens

type Checker m a = WriterT String (StateT ProvedMap (StateT MPMap (ReaderT (Hypothesises, Expr) m))) a
type CheckerT m = Checker m DefExpr

--IO
eof :: Checker IO Bool
eof = lift . lift . lift $ lift isEOF

myGetLine :: Checker IO String
myGetLine = lift . lift . lift $ lift getLine 

-- Reader
statement :: Checker IO Expr 
statement = lift . lift $ lift (asks snd)

hyps :: Checker IO Hypothesises
hyps = lift . lift $ lift (asks fst)

-- State
mpMapGet :: Checker IO MPMap
mpMapGet = lift $ lift get

prMapGet :: Checker IO ProvedMap
prMapGet = lift get

mpMapModify :: Expr -> Int -> Int -> ExprType -> CheckerT IO
mpMapModify expr i depth type' = 
    case expr of 
        Binary Impl l r -> do 
            lift . lift $ modify f
            checkEOF (DefExpr depth i type' expr) i
                where 
                    f  = Map.insertWith f' (right expr) [DefExpr depth i type' expr]
                    f' new old = new ++ old
        _               -> do 
            checkEOF (DefExpr depth i type' expr) i

prMapModify :: Expr -> Int -> Int -> ExprType -> CheckerT IO 
prMapModify expr i depth type' = do 
    lift $ modify f
    return (DefExpr depth i type' expr)
        where 
            f  = Map.insertWith f' expr (DefExpr depth i type' expr)
            f' new old = old 

--Writer
logMe :: String -> CheckerT IO
logMe s = do { tell s; return $ false' . parseExpression . alexScanTokens $ "Z" }


checkEOF :: DefExpr -> Int -> CheckerT IO
checkEOF def i = do 
    iEof <- eof 
    if iEof
    then do 
        s <- statement
        if _expr def /= s 
        then return (false' . parseExpression . alexScanTokens $ "Z")
        else return def
    else checker' (i+1)

checkMP :: [DefExpr] -> Int -> Maybe DefExpr -> CheckerT IO
checkMP [] _ Nothing     = return (false' . parseExpression . alexScanTokens $ "Z")    
checkMP [] i (Just full) = do 
    pr <- prMapGet
    
    let l = fromJust $ pr Map.!? (left . _expr $ full)
    let depth = _depth l + _depth full
    let type' = MP (_numStr l) (_numStr full)
    let r = right . _expr $ full
    logMe . show $ depth
    prMapModify r i depth type'
    mpMapModify r i depth type'

checkMP (x:xs) i Nothing = do 
    pr <- prMapGet
    let ll = pr Map.!? (left . _expr $ x)
    case ll of
        Just _  -> checkMP xs i (Just x)
        Nothing -> checkMP xs i Nothing

checkMP (x:xs) i (Just full) = do
    pr <- prMapGet
    let ll = pr Map.!? (left . _expr $ x)
    let l2 = fromJust $ pr Map.!? (left . _expr $ full)
    logMe . show $ _depth l2 
    case ll of
        Just l1 -> if _depth x <= _depth full  then do { logMe (show (_expr l2) ++ "\n"); checkMP xs i (Just x) } else checkMP xs i (Just full)
        Nothing -> checkMP xs i (Just full)


checker' :: Int -> CheckerT IO 
checker' i = do
    buff <- myGetLine
    let currentExpr = toE buff 
    let numAx = checkAxioms currentExpr
    if numAx /= 0
    then do
        prMapModify currentExpr i 1 (Ax numAx)
        mpMapModify currentExpr i 1 (Ax numAx)
    else do 
        h <- hyps
        let numHyp = checkHypothesises currentExpr h
        if numHyp /= 0 
        then do
            prMapModify currentExpr i 1 (Hyp numHyp)
            mpMapModify currentExpr i 1 (Hyp numHyp)
        else do
            mp <- mpMapGet
            let s = mp Map.!? currentExpr        
            case s of 
                Just s -> checkMP s i Nothing             
                _      -> return (false' currentExpr)
            
 


checker :: Expr -> Hypothesises -> ProvedMap -> MPMap -> IO (((DefExpr, String), ProvedMap), MPMap)
checker statement h p m = runReaderT (runStateT (runStateT (runWriterT (checker' 1)) p) m) (h, statement)