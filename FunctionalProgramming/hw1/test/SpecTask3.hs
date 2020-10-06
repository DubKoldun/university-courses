module SpecTask3
  (
    task3Test
  ) where

import Test.Tasty (TestTree)
import Data.List.NonEmpty (NonEmpty((:|)))

import Test.Tasty.Hspec (Spec, describe, it, shouldBe, testSpec)

import Task3

task3Test :: IO TestTree
task3Test = testSpec "Task 3" allTask3Tests

allTask3Tests :: Spec
allTask3Tests = do
  describe "isEmpty function" $
    it "cheking 'Tree' on emptiness" $ do
      isEmpty Leaf `shouldBe` True
      isEmpty (Branch Leaf ((42::Int) :| []) Leaf) `shouldBe` False
      isEmpty (fromList ((3::Int) : [1, 1]))       `shouldBe` False

  describe "size function" $
    it "returns the size of the tree" $ do
      size Leaf                              `shouldBe` 0
      size (Branch Leaf ((42::Int) :| []) Leaf)      `shouldBe` 1
      
      size (fromList ((1::Int) : [2, 3, 4])) `shouldBe` 4
      size (fromList ('a' : ['c', '4']))     `shouldBe` 3
      size (fromList ['0'])                `shouldBe` 1

  describe "contains function" $
    it "checks if an element is in the tree" $ do
      contains Leaf (42::Int) `shouldBe` False
      contains (Branch Leaf ((42::Int) :| []) Leaf) 42 `shouldBe` True
      
      contains (fromList ([4, 4, 4, 4]::[Int])) (4::Int)  `shouldBe` True
      contains (fromList ([1, 1, 1]::[Int]))    (10::Int) `shouldBe` False
      contains (fromList ([42, 0, 1]::[Int]))   0         `shouldBe` True

  describe "insert function" $
    it "inserts element in the tree" $ do
      toList (insert Leaf (42::Int)) `shouldBe` ([42]::[Int])
      toList (insert (Branch Leaf ((42::Int) :| []) Leaf) 42) `shouldBe` [42, 42]

      toList (insert (fromList ([84, 42, 21, 42]::[Int])) (25::Int)) `shouldBe` ([21, 25, 42, 42, 84]::[Int])
      toList (insert (fromList (['x', '1', 'Z']::[Char])) 'a')       `shouldBe` ['1', 'Z', 'a', 'x']
      toList (insert (fromList ([1, 1, 1]::[Int])) (1::Int))         `shouldBe` ([1, 1, 1, 1]::[Int])

  describe "fromList function" $
    it "converts list to tree" $ do
      toList Leaf `shouldBe` ([]::[Int])
      toList (Branch Leaf ((42::Int) :| []) Leaf) `shouldBe` ([42]::[Int])

      toList (fromList ([42, 42, 42, 42]::[Int]))   `shouldBe` [42, 42, 42, 42]
      toList (fromList ([1, 0, 0, 1, 0, 0]::[Int])) `shouldBe` [0, 0, 0, 0, 1, 1]
      toList (fromList (['x', '1', 'Z']::[Char]))   `shouldBe` ['1', 'Z', 'x']

  describe "remove function (remove given value from the tree)" $ do
    it "extreme cases" $ do
      toList (remove (fromList ([]::[Int])) 2)    `shouldBe` ([]::[Int])
      toList (remove (fromList ([2,2]::[Int])) 2) `shouldBe` ([2]::[Int])
      toList (remove (fromList ([0]::[Int])) 1)   `shouldBe` ([0]::[Int])
      toList (remove (fromList ([42]::[Int])) 42) `shouldBe` ([]::[Int])

    it "common cases" $ do
      toList (remove (fromList ([8, 2, 3, 4, 1, 2]::[Int])) 2)  `shouldBe` ([1, 2, 3, 4, 8]::[Int])
      toList (remove (fromList ([8, 2, 3, 4, 1, 2]::[Int])) 42) `shouldBe` ([1, 2, 2, 3, 4, 8]::[Int])
      



