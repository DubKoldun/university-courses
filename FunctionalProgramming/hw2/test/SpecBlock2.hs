module SpecBlock2
  (
    block2Test
  ) where

import Test.Tasty (TestTree)
import Test.Tasty.Hspec (Spec, describe, it, shouldBe, testSpec)

import Block2

block2Test :: IO TestTree
block2Test = testSpec "Block 2" allBlock2Tests

allBlock2Tests :: Spec
allBlock2Tests = do
  describe "Task 1. Check Expression implementation by 'eval' function" $ do
    it "'eval' success" $ do
      eval (Constant 0)  `shouldBe` Right 0
      eval (Constant 42) `shouldBe` Right 42

      eval (Sub (Constant 66) (Constant 24)) `shouldBe` Right 42
      eval (Mul (Add (Constant 11) (Constant (-7))) (Div (Constant 22) (Constant 11))) `shouldBe` Right 8
      eval (Mul (Add (Constant 11) (Constant (-7))) (Pow (Constant 100) (Constant 0))) `shouldBe` Right 4
    it "'eval' failure" $ do
      eval (Div (Constant 0) (Constant 0))                   `shouldBe` Left DivideByZero
      eval (Pow (Constant 0) (Constant (-2)))                `shouldBe` Left NegativePow
      eval (Div (Constant 22) (Constant 0))                  `shouldBe` Left DivideByZero
      eval (Pow (Constant 22) (Div (Constant 22) (Constant 0))) `shouldBe` Left DivideByZero

  describe "Task 2. Simple moving average algorithm implementation" $
    it "algorithm correctness check (funciton 'moving')" $ do
      moving 4 ([1, 5, 3, 8, 7, 9, 6] :: [Double])       `shouldBe` [1.0, 3.0, 3.0, 4.25, 5.75, 6.75, 7.5]
      moving 2 ([1, 5, 3, 8, 7, 9, 6] :: [Double])       `shouldBe` [1.0, 3.0, 4.0, 5.5, 7.5, 8.0, 7.5]
      moving 2 ([2, 2] :: [Double])                      `shouldBe` [2.0, 2.0]
      moving 5 ([2, 2] :: [Double])                     `shouldBe` [2.0, 2.0]
      moving 9 ([1, 2, 3, 4, 5, 6, 7, 8, 9] :: [Double]) `shouldBe` [1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0]
