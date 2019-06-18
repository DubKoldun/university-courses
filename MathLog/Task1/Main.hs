module Main where

import Grammar (Expr (..))
import Tokenizer (alexScanTokens)
import Parsenizer (parsing)

main :: IO ()
main = do
  input <- getLine
  let a = parsing (alexScanTokens input)
  putStrLn $ show a
