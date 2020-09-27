module Main where

import Parser.Analyzer (alexScanTokens)
import Parser.Parser (parser)

main :: IO ()
main = do
  input <- getLine
  let expr = parser (alexScanTokens input)
    in putStrLn $ show expr
