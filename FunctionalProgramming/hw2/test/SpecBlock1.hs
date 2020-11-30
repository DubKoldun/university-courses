module SpecBlock1
  (
    block1Test
  ) where

import Test.Tasty (TestTree)
import Test.Tasty.Hspec (Spec, describe, it, shouldBe, testSpec)

import Block1

block1Test :: IO TestTree
block1Test = testSpec "Block 1" allBlock1Tests

defaultTree :: Tree Int
defaultTree = Branch (Leaf 1) (Leaf 2)

defaultTree3 :: Tree Int
defaultTree3 = Branch (Leaf (-1)) (Leaf (-2))

defaultTree4 :: Tree Int
defaultTree4 = Branch (Branch (Leaf 1) (Leaf 2)) (Branch (Leaf (-2)) (Leaf 0))

defaultFunctionTree :: Tree (Int -> Int)
defaultFunctionTree = Branch (Leaf (+1)) (Leaf (*3))

defaultFunctionTree1 :: Tree (Int -> Int)
defaultFunctionTree1 = Branch (Leaf (*5)) (Leaf (div 2))

defaultFunctionTree2 :: Tree (Int -> Int)
defaultFunctionTree2 = Branch (Leaf (^(0 :: Int)) ) (Leaf (*2))

fun4Traverse :: Int -> Maybe Bool
fun4Traverse x = if x < 0 then Just False else Just True

fun4Traverse2 :: Int -> Either String Bool
fun4Traverse2 x = if x < 0 then Left "Something happens" else Right True

defaultNonEmpty :: NonEmpty Int
defaultNonEmpty = 0 :| [1,2,3,4,5]

defaultNonEmpty2 :: NonEmpty Int
defaultNonEmpty2 = 42 :| [0,0,0,0,0]

defaultNonEmpty3 :: NonEmpty Int
defaultNonEmpty3 = (-1) :| [1,2,-3,42]

defaultFunctionNonEmpty :: NonEmpty (Int -> Int)
defaultFunctionNonEmpty = (+1) :| [(*3)]

defaultFunctionNonEmpty1 :: NonEmpty (Int -> Int)
defaultFunctionNonEmpty1 = (*5) :| [(^(2::Int))]

fun4Monad :: Int -> NonEmpty String
fun4Monad x = show x :| []

fun4Monad2 :: String -> NonEmpty Int
fun4Monad2 x = length x :| []

allBlock1Tests :: Spec
allBlock1Tests = do
  describe "Task1. stringSum function" $
    it "returns the sum of elements in string" $ do
      stringSum "22 33 11 0 1" `shouldBe` Just 67
      stringSum "1, 2 3 4"     `shouldBe` Nothing
      stringSum "1L k 12"      `shouldBe` Nothing
      stringSum "12  13    12" `shouldBe` Just 37
      stringSum "1"            `shouldBe` Just 1


  describe "Task2. Instances for Tree data type" $ do
    it "Functor laws" $ do
      (fmap id :: Tree Int -> Tree Int) defaultTree  `shouldBe` id defaultTree
      fmap ((*3) . (+1)) defaultTree                 `shouldBe` ((fmap (*3) :: Tree Int -> Tree Int) . (fmap (+1) :: Tree Int ->  Tree Int) $ defaultTree)

    it "Functor tests" $ do
      fmap ((*3) . (+1)) defaultTree `shouldBe` Branch (Leaf 6 :: Tree Int) (Leaf 9)
      fmap ((*3) . (+1)) (Leaf 0)    `shouldBe` (Leaf 3 :: Tree Int)

    it "Applicative laws" $ do
      (pure id :: Tree (a -> a))   <*> defaultTree    `shouldBe` defaultTree
      (pure (+1) :: Tree (Int -> Int)) <*> pure 1     `shouldBe` (pure ((+1) 1) :: Tree Int)
      (defaultFunctionTree <*> (pure 10 :: Tree Int)) `shouldBe` ((pure ($ 10) :: Tree ((Int -> Int) -> Int)) <*> defaultFunctionTree)
      ((pure (.) :: Tree ((Int -> Int) -> (Int -> Int) -> Int -> Int)) <*> defaultFunctionTree <*> defaultFunctionTree1 <*> defaultTree) `shouldBe` (defaultFunctionTree <*> (defaultFunctionTree1 <*> defaultTree))

    it "Applicative tests" $ do
      (pure 2 :: Tree Int) `shouldBe` Leaf 2
      defaultFunctionTree <*> defaultTree `shouldBe` Branch (Branch (Leaf 2) (Leaf 3)) (Branch (Leaf 3) (Leaf 6))
      pure (.) <*> defaultFunctionTree <*> defaultFunctionTree2 <*> (pure 1 :: Tree Int) `shouldBe` Branch (Branch (Leaf 2) (Leaf 3)) (Branch (Leaf 3) (Leaf 6))

    it "Foldable tests" $ do
      foldr (+) 0 defaultTree  `shouldBe` 3
      foldr (*) 1 defaultTree  `shouldBe` 2
      foldr (+) 0 defaultTree4 `shouldBe` 1

    it "Traverse tests" $ do
      traverse fun4Traverse defaultTree   `shouldBe` Just  (Branch (Leaf True) (Leaf True))
      traverse fun4Traverse defaultTree3  `shouldBe` Just  (Branch (Leaf False) (Leaf False))
      traverse fun4Traverse defaultTree4  `shouldBe` Just  (Branch (Branch (Leaf True) (Leaf True)) (Branch (Leaf False) (Leaf True)))
      traverse fun4Traverse2 defaultTree4 `shouldBe` Left "Something happens"

  describe "Task3. Instances for NonEmpty data type" $ do
    it "Functor laws" $ do
      (fmap id :: NonEmpty Int -> NonEmpty Int) defaultNonEmpty  `shouldBe` id defaultNonEmpty
      fmap ((*3) . (+1)) defaultNonEmpty `shouldBe` ((fmap (*3) :: NonEmpty Int -> NonEmpty Int) . (fmap (+1) :: NonEmpty Int ->  NonEmpty Int) $ defaultNonEmpty)

    it "Functor tests" $ do
      fmap ((*3) . (+1)) defaultNonEmpty `shouldBe` 3 :| [6,9,12,15,18]
      fmap ((*3) . (+1)) (0 :| [])       `shouldBe` (3 :| [] :: NonEmpty Int)

    it "Applicative laws" $ do
      (pure id :: NonEmpty (a -> a))   <*> defaultNonEmpty `shouldBe` defaultNonEmpty
      (pure (+1) :: NonEmpty (Int -> Int)) <*> pure 1      `shouldBe` (pure ((+1) 1) :: NonEmpty Int)
      (defaultFunctionNonEmpty <*> (pure 10 :: NonEmpty Int)) `shouldBe` ((pure ($ 10) :: NonEmpty ((Int -> Int) -> Int)) <*> defaultFunctionNonEmpty)
      ((pure (.) :: NonEmpty ((Int -> Int) -> (Int -> Int) -> Int -> Int)) <*> defaultFunctionNonEmpty <*> defaultFunctionNonEmpty1 <*> defaultNonEmpty) `shouldBe` (defaultFunctionNonEmpty <*> (defaultFunctionNonEmpty1 <*> defaultNonEmpty))

    it "Foldable tests" $ do
      foldr (+) 0 defaultNonEmpty  `shouldBe` 15
      foldr (*) 1 defaultNonEmpty  `shouldBe` 0
      foldr (*) 1 defaultNonEmpty2 `shouldBe` 0
      foldr (+) 0 defaultNonEmpty2 `shouldBe` 42

    it "Traverse tests" $ do
      traverse fun4Traverse  defaultNonEmpty   `shouldBe` Just  (True  :| [True, True, True, True, True])
      traverse fun4Traverse  defaultNonEmpty3  `shouldBe` Just  (False :| [True, True, False, True])
      traverse fun4Traverse2 defaultNonEmpty3  `shouldBe` Left "Something happens"

    it "Monad laws" $ do
      ((return :: Int -> NonEmpty Int) 1 >>= fun4Monad)      `shouldBe` fun4Monad 1
      (defaultNonEmpty2 >>= (return :: Int -> NonEmpty Int)) `shouldBe` defaultNonEmpty2
      ((defaultNonEmpty3 >>= fun4Monad) >>= fun4Monad2 )     `shouldBe` (defaultNonEmpty3 >>= (\x -> fun4Monad x >>= fun4Monad2))





