module SpecTask2 
  (
    task2Test
  ) where

import Test.Tasty (TestTree)
import Test.Tasty.Hspec (Spec, describe, it, shouldBe, testSpec)

import Task2

task2Test :: IO TestTree
task2Test = testSpec "Task 2" allTask2Tests

allTask2Tests :: Spec
allTask2Tests = do
  describe "natSum function" $ 
    it "returns sum of two 'Nat' numbers" $ do
      natSum (S (S Z)) Z             `shouldBe` S (S Z)
      natSum (S (S (S Z))) (S (S Z)) `shouldBe` S (S (S (S (S Z)))) 

      natSum (toEnum 3)   (toEnum 1)   `shouldBe` natSum (toEnum 2) (toEnum 2)
      natSum (toEnum 3)   (toEnum 1)   `shouldBe` toEnum 4
      natSum (toEnum 12)  (toEnum 777) `shouldBe` toEnum 789
      natSum (toEnum 100) (toEnum 2)   `shouldBe` toEnum 102

  describe "natMul function" $
    it "returns multiplication of two 'Nat' numbers" $ do
      natMul (S (S Z)) Z             `shouldBe` Z
      natMul (S (S Z)) (S (S (S Z))) `shouldBe` S (S (S (S (S (S Z)))))

      natMul (toEnum 2)  (toEnum 4)  `shouldBe` toEnum 8
      natMul (toEnum 3)  (toEnum 7)  `shouldBe` toEnum 21
      natMul (toEnum 1)  (toEnum 1)  `shouldBe` toEnum 1
      natMul (toEnum 0)  (toEnum 30) `shouldBe` toEnum 0

  describe "natSub function" $
    it "returns substraction of two 'Nat' numbers" $ do
      natSub (S (S Z)) (S Z)         `shouldBe` S Z
      natSub (S (S Z)) (S (S (S Z))) `shouldBe` Z

      natSub (toEnum 0)  (toEnum 20) `shouldBe` toEnum 0
      natSub (toEnum 10) (toEnum 5)  `shouldBe` toEnum 5
      natSub (toEnum 31) (toEnum 1)  `shouldBe` toEnum 30

  describe "toNat function" $
    it "convert 'Int' to 'Nat'" $ do
      toNat (-4) `shouldBe` Z
      toNat 1    `shouldBe` S Z
      toNat 0    `shouldBe` Z
      toNat 4    `shouldBe` S (S (S (S Z)))

  describe "fromNat function" $
    it "convert 'Nat' to 'Int'" $ do
      fromNat Z         `shouldBe` 0
      fromNat (S Z)     `shouldBe` 1
      fromNat (S (S Z)) `shouldBe` 2

  describe "equality check" $
    it "checking on equality of two 'Nat'" $ do
      (==) (toNat 2)  (toNat 2)      `shouldBe` True
      (==) (toNat (-1)) (toNat (-5)) `shouldBe` True

      (==) (toNat 1)  (toNat 0)      `shouldBe` False

  describe "comparsion check" $
    it "checking on correct comparing of two 'Nat'" $ do
      compare (toNat 2)    (toNat 2)  `shouldBe` EQ
      compare (toNat (-1)) (toNat (-5)) `shouldBe` EQ

      compare (toNat 1)   (toNat 0)   `shouldBe` GT
      compare (toNat 12)  (toNat 11)  `shouldBe` GT

      compare (toNat 3) (toNat 7)  `shouldBe` LT

  describe "isEven function" $
    it "check if 'Nat' number is even" $ do
      isEven (toEnum 0   :: Nat) `shouldBe` True
      isEven (toEnum 1   :: Nat) `shouldBe` False
      isEven (toEnum 2   :: Nat) `shouldBe` True

      isEven (toEnum 42 :: Nat) `shouldBe` True

  describe "natDiv function" $
    it "returns integer division of two 'Nat' numbers" $ do
      natDiv (S (S Z)) (S Z)         `shouldBe` S (S Z)
      natDiv (S (S Z)) (S (S (S Z))) `shouldBe` Z

      natDiv (toEnum 0)  (toEnum 20) `shouldBe` toEnum 0
      natDiv (toEnum 10) (toEnum 5)  `shouldBe` toEnum 2
      natDiv (toEnum 31) (toEnum 1)  `shouldBe` toEnum 31

  describe "natMod function" $
    it "returns modulo of two 'Nat' numbers" $ do
      natMod (S (S Z)) (S Z)         `shouldBe` Z
      natMod (S (S Z)) (S (S (S Z))) `shouldBe` S (S Z)

      natMod (toEnum 21) (toEnum 20) `shouldBe` toEnum 1
      natMod (toEnum 10) (toEnum 5)  `shouldBe` toEnum 0
      natMod (toEnum 5)  (toEnum 3)  `shouldBe` toEnum 2