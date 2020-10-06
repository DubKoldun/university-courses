  module SpecTask6
  (
    task6Test
  ) where

import Data.Monoid (Sum(..), Product(..))
import Test.Tasty (TestTree)
import Test.Tasty.Hspec (Spec, describe, it, shouldBe, testSpec)

import Task6

task6Test :: IO TestTree
task6Test = testSpec "Task 6" allTask6Tests

allTask6Tests :: Spec
allTask6Tests = do
  describe "maybeConcat function" $
    it "takes 'Maybe' from list and concatenates all elements of inner list" $ do
      maybeConcat []                                 `shouldBe` ([] :: [Int])
      maybeConcat [Nothing, Nothing]                 `shouldBe` ([] :: [Int])
      maybeConcat [Nothing, Just ['c', 'c', 'c']]    `shouldBe` ['c', 'c', 'c']
      maybeConcat [Just ([2, 1, 1, 4] :: [Int])]     `shouldBe` [2, 1, 1, 4]
      maybeConcat [Just ([1, 1, 2]::[Int]), Nothing] `shouldBe` [1, 1, 2]

      maybeConcat [Nothing, Just ([12, 13, 14] :: [Int]), Nothing, Just [0, 1]] `shouldBe` [12, 13, 14, 0, 1]
      maybeConcat [Just ([1,2,3]::[Int]), Nothing, Just [4,5]]                  `shouldBe` [1, 2, 3, 4, 5]

  describe "eitherConcat function" $
    it "separates 'Either' and union elements according to their types" $ do
      eitherConcat [Left (Sum (3::Int)), Right ([1,2,3]::[Int]), Left (Sum 5), Right [4,5]] `shouldBe` (Sum {getSum = 8::Int}, [1,2,3,4,5]::[Int])
      eitherConcat [Left (Product (3::Int))] `shouldBe` (Product {getProduct = 3::Int}, ())