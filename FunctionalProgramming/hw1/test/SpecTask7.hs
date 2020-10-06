module SpecTask7 
  (
     task7Test
  ) where

import Test.Tasty (TestTree)
import Test.Tasty.Hspec (Spec, describe, it, shouldBe, testSpec)

import Task7

task7Test :: IO TestTree
task7Test = testSpec "Task 7" allTask7Tests

allTask7Tests :: Spec
allTask7Tests = do
  describe "NonEmpty type" $
    it "checks on associativity (semigroup rule)" $ do
      ((21 :: Int) :| []) <> ((42 :| []) <> (84 :| [])) `shouldBe` (((21 :: Int) :| []) <> (42 :| [])) <> (84 :| [])
      ((0 :: Int) :| [])  <> (1 :| [])   <> (2 :| [])   `shouldBe` ((0 :: Int) :| [1, 2])

  describe "ThisOrThat type" $
    it "checks on associativity (semigroup rule)" $ do
      (This 1 :: ThisOrThat Int Int) <> (This 2 <> This 3)       `shouldBe` ((This 1 :: ThisOrThat Int Int) <> This 2) <> This 3
      (This 1 :: ThisOrThat Int Int) <> (This 2 <> That 3)       `shouldBe` ((This 1 :: ThisOrThat Int Int) <> This 2) <> That 3
      (This 1 :: ThisOrThat Int Int) <> (This 2 <> Both 3 4)     `shouldBe` ((This 1 :: ThisOrThat Int Int) <> This 2) <> Both 3 4
      (This 1 :: ThisOrThat Int Int) <> (That 2 <> This 3)       `shouldBe` ((This 1 :: ThisOrThat Int Int) <> That 2) <> This 3
      (This 1 :: ThisOrThat Int Int) <> (That 2 <> That 3)       `shouldBe` ((This 1 :: ThisOrThat Int Int) <> That 2) <> That 3
      (This 1 :: ThisOrThat Int Int) <> (That 2 <> Both 3 4)     `shouldBe` ((This 1 :: ThisOrThat Int Int) <> That 2) <> Both 3 4
      (This 1 :: ThisOrThat Int Int) <> (Both 2 3 <> This 4)     `shouldBe` ((This 1 :: ThisOrThat Int Int) <> Both 2 3) <> This 4
      (This 1 :: ThisOrThat Int Int) <> (Both 2 3 <> That 4)     `shouldBe` ((This 1 :: ThisOrThat Int Int) <> Both 2 3) <> That 4
      (This 1 :: ThisOrThat Int Int) <> (Both 2 3 <> Both 4 5)   `shouldBe` ((This 1 :: ThisOrThat Int Int) <> Both 2 3) <> Both 4 5
      (That 1 :: ThisOrThat Int Int) <> (This 2 <> This 3)       `shouldBe` ((That 1 :: ThisOrThat Int Int) <> This 2) <> This 3
      (That 1 :: ThisOrThat Int Int) <> (This 2 <> That 3)       `shouldBe` ((That 1 :: ThisOrThat Int Int) <> This 2) <> That 3
      (That 1 :: ThisOrThat Int Int) <> (This 2 <> Both 3 4)     `shouldBe` ((That 1 :: ThisOrThat Int Int) <> This 2) <> Both 3 4
      (That 1 :: ThisOrThat Int Int) <> (That 2 <> This 3)       `shouldBe` ((That 1 :: ThisOrThat Int Int) <> That 2) <> This 3
      (That 1 :: ThisOrThat Int Int) <> (That 2 <> That 3)       `shouldBe` ((That 1 :: ThisOrThat Int Int) <> That 2) <> That 3
      (That 1 :: ThisOrThat Int Int) <> (That 2 <> Both 3 4)     `shouldBe` ((That 1 :: ThisOrThat Int Int) <> That 2) <> Both 3 4
      (That 1 :: ThisOrThat Int Int) <> (Both 2 3 <> This 4)     `shouldBe` ((That 1 :: ThisOrThat Int Int) <> Both 2 3) <> This 4
      (That 1 :: ThisOrThat Int Int) <> (Both 2 3 <> That 4)     `shouldBe` ((That 1 :: ThisOrThat Int Int) <> Both 2 3) <> That 4
      (That 1 :: ThisOrThat Int Int) <> (Both 2 3 <> Both 4 5)   `shouldBe` ((That 1 :: ThisOrThat Int Int) <> Both 2 3) <> Both 4 5
      (Both 0 1 :: ThisOrThat Int Int) <> (This 2 <> This 3)     `shouldBe` ((Both 0 1 :: ThisOrThat Int Int) <> This 2) <> This 3
      (Both 0 1 :: ThisOrThat Int Int) <> (This 2 <> That 3)     `shouldBe` ((Both 0 1 :: ThisOrThat Int Int) <> This 2) <> That 3 
      (Both 0 1 :: ThisOrThat Int Int) <> (This 2 <> Both 3 4)   `shouldBe` ((Both 0 1 :: ThisOrThat Int Int) <> This 2) <> Both 3 4
      (Both 0 1 :: ThisOrThat Int Int) <> (That 2 <> This 3)     `shouldBe` ((Both 0 1 :: ThisOrThat Int Int) <> That 2) <> This 3
      (Both 0 1 :: ThisOrThat Int Int) <> (That 2 <> That 3)     `shouldBe` ((Both 0 1 :: ThisOrThat Int Int) <> That 2) <> That 3
      (Both 0 1 :: ThisOrThat Int Int) <> (That 2 <> Both 3 4)   `shouldBe` ((Both 0 1 :: ThisOrThat Int Int) <> That 2) <> Both 3 4
      (Both 0 1 :: ThisOrThat Int Int) <> (Both 2 3 <> This 4)   `shouldBe` ((Both 0 1 :: ThisOrThat Int Int) <> Both 2 3) <> This 4
      (Both 0 1 :: ThisOrThat Int Int) <> (Both 2 3 <> That 4)   `shouldBe` ((Both 0 1 :: ThisOrThat Int Int) <> Both 2 3) <> That 4
      (Both 0 1 :: ThisOrThat Int Int) <> (Both 2 3 <> Both 4 5) `shouldBe` ((Both 0 1 :: ThisOrThat Int Int) <> Both 2 3) <> Both 4 5

  describe "Str type (concatenation with dot)" $ do
    it "checks on identity rules (monoid)" $ do
      Str "root" <> Str "server" `shouldBe` Str "root.server"
      Str "" <> Str "server"     `shouldBe` Str "server" 
      Str "root" <> Str ""       `shouldBe` Str "root"
    
    it "checks on associativity rules (semigroup)" $ do
      Str "root" <> (Str "server" <> Str "222") `shouldBe` (Str "root" <> Str "server") <> Str "222"
      Str "" <> (Str "server" <> Str "222")     `shouldBe` (Str "" <> Str "server") <> Str "222"
  

