module Spec where

import Test.Tasty (defaultMain, testGroup)

import SpecBlock1 (block1Test)
import SpecBlock2 (block2Test)
import SpecBlock3 (block3Test)

main :: IO ()
main = do
  unitTests1 <- block1Test
  unitTests2 <- block2Test
  unitTests3 <- block3Test
  let allTests = testGroup "Homework 2" [ unitTests1, unitTests2, unitTests3 ]
    in defaultMain allTests
