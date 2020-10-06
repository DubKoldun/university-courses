module SpecTask4
  (
    task4Test
  ) where

import Test.Tasty (TestTree)

import Test.Tasty.Hspec (Spec, describe, it, shouldBe, testSpec)

import Task3 (fromList, toList)

task4Test :: IO TestTree
task4Test = testSpec "Task 4" allTask4Tests

allTask4Tests :: Spec
allTask4Tests = do
  describe "check for correctness of 'Foldable' implementation for 'Tree'" $
    it "toList . fromList === sort" $ do
      toList (fromList ['x', '1', '2', 'x', 'x'])        `shouldBe` ['1', '2', 'x', 'x', 'x']
      toList (fromList ([]::[Int]))                      `shouldBe` ([]::[Int])
      toList (fromList ([4, 4, 4, 3, 2, 111, 3]::[Int])) `shouldBe` ([2, 3, 3, 4, 4, 4, 111]::[Int])
      toList (fromList ([112, 111]::[Int]))              `shouldBe` ([111, 112]::[Int])

