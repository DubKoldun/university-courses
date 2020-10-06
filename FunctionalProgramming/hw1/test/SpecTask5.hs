module SpecTask5 
  (
    task5Test
  ) where

import Data.List.NonEmpty (NonEmpty ((:|)))
import Test.Tasty (TestTree)
import Test.Tasty.Hspec (Spec, describe, it, shouldBe, testSpec)


import Task5

task5Test :: IO TestTree
task5Test = testSpec "Task 5" allTask5Tests

allTask5Tests :: Spec
allTask5Tests = do
  describe "splitOn function" $
    it "splits list by given separator" $ do
      splitOn '/' "path/to/file"   `shouldBe` ("path" :| ["to", "file"])
      splitOn '/' "/path/to/file/" `shouldBe` ("" :| ["path", "to", "file", ""])
      splitOn '!' "!!"             `shouldBe` ("" :| ["", ""])

  describe "joinWith function" $ do
    it "concatenates list of blocks with given joiner (reverse splitOn)" $ do
      joinWith '/' ("path" :| ["to", "file"])         `shouldBe` "path/to/file"
      joinWith '/' ("" :| ["path", "to", "file", ""])  `shouldBe` "/path/to/file/"
      joinWith '!' ("" :| ["", ""]) `shouldBe` "!!"

    it "checks on 'joinWith x . splitOn x === id" $ do
      (joinWith '/' . splitOn '/' $ "/path/to/file/") `shouldBe` "/path/to/file/"