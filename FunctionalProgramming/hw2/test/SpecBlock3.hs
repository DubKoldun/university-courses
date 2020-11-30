module SpecBlock3
  (
    block3Test
  ) where

import Test.Tasty (TestTree)
import Test.Tasty.Hspec (Spec, describe, it, shouldBe, testSpec)

import Block3

block3Test :: IO TestTree
block3Test = testSpec "Block 3" allBlock3Tests

allBlock3Tests :: Spec
allBlock3Tests = do
  describe "Task2. Parser combinators." $ do
    it "'ok' combinator tests" $ do
      runParser ok ""              `shouldBe` Just ((), [])
      runParser ok ([] :: [Char])  `shouldBe` Just ((), "")
      runParser ok "kekw"          `shouldBe` Just ((), "kekw")
      runParser ok ([42] :: [Int]) `shouldBe` Just ((), [42])

    it "'eof' combinator tests'" $ do
      runParser eof ""             `shouldBe` Just ((), [])
      runParser eof ([] :: [Char]) `shouldBe` Just ((), "")
      runParser eof "kekw"         `shouldBe` Nothing
      runParser eof ([42] :: [Int]) `shouldBe` Nothing

    it "'satisfy' combinator tests" $ do
      runParser (satisfy (== '1')) "1"                    `shouldBe` Just ('1', [])
      runParser (satisfy (== '2')) "24"                   `shouldBe` Just ('2', "4")
      runParser (satisfy (== "Hello")) ["Hello", "Hello"] `shouldBe` Just ("Hello", ["Hello"])
      runParser (satisfy (== (42 :: Int))) [42]           `shouldBe` Just (42, [])
      runParser (satisfy (== ([42] :: [Int]))) [[42]]     `shouldBe` Just ([42], [])

      runParser (satisfy (== ' ')) ""                 `shouldBe` Nothing
      runParser (satisfy (== 'h')) "b"                `shouldBe` Nothing
      runParser (satisfy (== "Hello")) ["Bye"]        `shouldBe` Nothing
      runParser (satisfy (== (24 :: Int))) [42]       `shouldBe` Nothing
      runParser (satisfy (== ([24] :: [Int]))) [[42]] `shouldBe` Nothing

    it "'element' combinator tests" $ do
      runParser (element ' ') "  "               `shouldBe` Just (' ', " ")
      runParser (element 'h') "hello"            `shouldBe` Just ('h', "ello")
      runParser (element 42) ([42, 24] :: [Int]) `shouldBe` Just (42, [24])

      runParser (element 'h') "olleh"            `shouldBe` Nothing
      runParser (element 42) ([24, 42] :: [Int]) `shouldBe` Nothing

    it "'stream' combinator tests" $ do
      runParser (stream "Hello") "Hello, world"   `shouldBe` Just ("Hello", ", world")
      runParser (stream ([42] :: [Int])) [42, 24] `shouldBe` Just ([42], [24])

      runParser (stream "  ")   "1   "     `shouldBe` Nothing
      runParser (stream "Hello")   "hello" `shouldBe` Nothing
      runParser (stream ([42, 24] :: [Int])) [24, 42, 24] `shouldBe` Nothing

  describe "Task3. Simple parsers." $ do
    it "'correctBracketSequence' parser tests" $ do
      runParser correctBracketSequence ""         `shouldBe` Just ((), [])
      runParser correctBracketSequence "()"       `shouldBe` Just ((), [])
      runParser correctBracketSequence "(()())()" `shouldBe` Just ((), [])

      runParser correctBracketSequence " "       `shouldBe` Nothing
      runParser correctBracketSequence "("       `shouldBe` Nothing
      runParser correctBracketSequence ")"       `shouldBe` Nothing
      runParser correctBracketSequence "()("     `shouldBe` Nothing
      runParser correctBracketSequence "(()()))" `shouldBe` Nothing
      runParser correctBracketSequence "(((()))" `shouldBe` Nothing

    it "'integer' parser tests" $ do
      runParser integer "42"    `shouldBe` Just (42, [])
      runParser integer "+42"   `shouldBe` Just (42, [])
      runParser integer "-42"   `shouldBe` Just (-42, [])
      runParser integer "+4x2"  `shouldBe` Just (4, "x2")
      runParser integer "42-42" `shouldBe` Just (42,"-42")

      runParser integer " "    `shouldBe` Nothing
      runParser integer "-"    `shouldBe` Nothing
      runParser integer "+"    `shouldBe` Nothing
      runParser integer ":(42" `shouldBe` Nothing
