module SpecTask1 
  (
    task1Test
  ) where

import Test.Tasty (TestTree)
import Test.Tasty.Hspec (Spec, describe, it, shouldBe, testSpec)

import Task1

task1Test :: IO TestTree
task1Test = testSpec "Task 1" allTask1Tests

allTask1Tests :: Spec
allTask1Tests = do
  describe "nextDay function" $
    it "returns the next day" $ do
      nextDay Monday    `shouldBe` Tuesday
      nextDay Tuesday   `shouldBe` Wednesday
      nextDay Wednesday `shouldBe` Thursday
      nextDay Thursday  `shouldBe` Friday
      nextDay Friday    `shouldBe` Saturday
      nextDay Saturday  `shouldBe` Sunday
      nextDay Sunday    `shouldBe` Monday

  describe "afterDays function" $
    it "returns the day which follow after the given number of days from taken" $ do
      afterDays Monday 0    `shouldBe` Monday
      afterDays Monday 1    `shouldBe` Tuesday
      afterDays Monday 2    `shouldBe` Wednesday
      afterDays Monday 3    `shouldBe` Thursday
      afterDays Monday 4    `shouldBe` Friday
      afterDays Monday 5    `shouldBe` Saturday
      afterDays Monday 6    `shouldBe` Sunday
      afterDays Monday 7    `shouldBe` Monday
      afterDays Monday 8    `shouldBe` Tuesday
      afterDays Monday (-8) `shouldBe` Sunday

      afterDays Tuesday   (-8)  `shouldBe` Monday 
      afterDays Wednesday 14    `shouldBe` Wednesday 
      afterDays Thursday  (-14) `shouldBe` Thursday
      afterDays Friday    (-36) `shouldBe` Thursday
      afterDays Saturday  9     `shouldBe` Monday
      afterDays Sunday    13    `shouldBe` Saturday
      
  describe "isWeekend function" $
    it "checks if the day of the week is a weekend" $ do
      isWeekend Monday    `shouldBe` False
      isWeekend Tuesday   `shouldBe` False
      isWeekend Wednesday `shouldBe` False
      isWeekend Thursday  `shouldBe` False
      isWeekend Friday    `shouldBe` False
      isWeekend Saturday  `shouldBe` True
      isWeekend Sunday    `shouldBe` True

  describe "daysToParty function" $
    it "returns amount of days til the party" $ do
      daysToParty Monday    `shouldBe` 4
      daysToParty Tuesday   `shouldBe` 3
      daysToParty Wednesday `shouldBe` 2
      daysToParty Thursday  `shouldBe` 1
      daysToParty Friday    `shouldBe` 0
      daysToParty Saturday  `shouldBe` 6
      daysToParty Sunday    `shouldBe` 5
