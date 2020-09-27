module Algo.Recovery where

import Data.Maybe (fromJust)
import qualified Data.Map as Map (Map, empty, fromList, toList, (!?), insert)

import Control.Monad.Trans (lift)
import Control.Monad.Trans.Reader (ReaderT(..), asks)
import Control.Monad.Trans.State (StateT(..), get, put, modify)

import DSrealization.Expression (ExprType(..), Expr(..), DefExpr(..), Operation(..)) 

type RevProvedMap = Map.Map Int DefExpr 
type ProvedMap    = Map.Map Expr DefExpr 

type Recover m a = ReaderT RevProvedMap (StateT RevProvedMap m) a
type RecoverT m = Recover m ()

currentState :: Recover IO RevProvedMap
currentState = lift get 

modifyState :: DefExpr -> RecoverT IO
modifyState def = do 
    lift $ modify f where 
        f = Map.insert (_numStr def) def
 

recovery' :: DefExpr -> RecoverT IO 
recovery' currentExpr = 
    case currentExpr of
        DefExpr _ _ (Ax _) _  -> modifyState currentExpr
        DefExpr _ _ (Hyp _) _ -> modifyState currentExpr
        DefExpr _ _ (MP from to) _ -> do
            newExpr1 <- asks (Map.!? from) 
            recovery' $ fromJust newExpr1
            newExpr2 <- asks (Map.!? to)
            recovery' $ fromJust newExpr2
            modifyState currentExpr


reversePR :: [(Expr, DefExpr)] -> RevProvedMap -> RevProvedMap 
reversePR []     rpm = rpm
reversePR (x:xs) rpm = reversePR xs (Map.insert numb expr rpm) where 
    expr = snd x
    numb = _numStr expr

recovery :: ProvedMap -> DefExpr -> IO ((), RevProvedMap)
recovery pr e = runStateT (runReaderT (recovery' e) (reversePR (Map.toList pr) Map.empty)) Map.empty