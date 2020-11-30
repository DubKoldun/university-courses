{-# LANGUAGE InstanceSigs #-}

-- | Block 1 of functional programming homework
module Block1
  ( NonEmpty(..)
  , Tree(..)

  , stringSum
  ) where

import Text.Read (readMaybe)

-- Task 1

-- | Calculates sum  of elements in string
-- or failes when parsing error happened
stringSum
  :: String -- ^ given string
  -> Maybe Int -- ^ result or Nothing when failed
stringSum = fmap sum . traverse readMaybe . words
-- Task 2

-- | Data type for Tree implementation
data Tree a
  = Branch (Tree a) (Tree a)
  | Leaf a
  deriving (Eq, Show)

instance Functor Tree where
  fmap :: (a -> b) -> Tree a -> Tree b
  fmap f (Leaf a) = Leaf (f a)
  fmap f (Branch l r) = Branch (fmap f l) (fmap f r)

instance Applicative Tree where
  pure :: a -> Tree a
  pure = Leaf

  (<*>) :: Tree (a -> b) -> Tree a -> Tree b
  (<*>) (Leaf f) x = fmap f x
  (<*>) (Branch l r) x = Branch (l <*> x) (r <*> x)

instance Foldable Tree where
  foldr :: (a -> b -> b) -> b -> Tree a -> b
  foldr f ini (Leaf a) = f a ini
  foldr f ini (Branch l r) = foldr f (foldr f ini l) r

instance Traversable Tree where
  traverse :: (Applicative f) => (a -> f b) -> Tree a -> f (Tree b)
  traverse f (Leaf a) = Leaf <$> f a
  traverse f (Branch l r) = Branch <$> traverse f l <*> traverse f r

-- Task 3

-- | Data type for non empty list
data NonEmpty a = a :| [a]
  deriving (Show, Eq)

instance Functor NonEmpty where
  fmap :: (a -> b) -> NonEmpty a -> NonEmpty b
  fmap f (x :| xs) = f x :| fmap f xs

instance Applicative NonEmpty where
  pure :: a -> NonEmpty a
  pure = (:| [])

  (<*>) :: NonEmpty (a -> b) -> NonEmpty a -> NonEmpty b
  (<*>) (f :| fs) (x :| xs) = f x :| (fmap f xs ++ (fs <*> (x:xs)))

instance Foldable NonEmpty where
  foldr :: (a -> b -> b) -> b -> NonEmpty a -> b
  foldr f ini (x :| xs) = f x (foldr f ini xs)

instance Traversable NonEmpty where
  traverse :: (Applicative f) => (a -> f b) -> NonEmpty a -> f (NonEmpty b)
  traverse f (x :| xs) = (:|) <$> f x <*> traverse f xs

instance Monad NonEmpty where
  return :: a -> NonEmpty a
  return = pure

  (>>=) :: NonEmpty a -> (a -> NonEmpty b) -> NonEmpty b
  (>>=) (x :| xs) f = b :| (bs ++ bs')
    where b :| bs = f x
          bs' = xs >>= toListF . f
          toListF (y :| ys) = y:ys

