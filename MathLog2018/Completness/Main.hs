module Main where

import Parser.Analyzer (alexScanTokens)
import Parser.Parser (parseExpression)
import DSrealization.Expression (Expr(..))


toHA :: String -> IO HypotAndAns
toHA = return . parseFirstLine . alexScanTokens 

toExpr :: String -> IO Expr
toExpr = return . parseExpression . alexScanTokens

main :: IO ()
main = do
    input <- getLine
    expr <- toExpr input

    return ()