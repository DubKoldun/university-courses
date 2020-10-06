{-# LANGUAGE InstanceSigs #-}

module Task7 
  (
    Endo(..)
  , NonEmpty(..)
  , Str(..)  
  , ThisOrThat(..)
  ) where 

data NonEmpty a = a :| [a]
  deriving (Show, Eq)

instance Semigroup (NonEmpty a) where
  (<>) :: NonEmpty a -> NonEmpty a -> NonEmpty a
  (<>) (x :| xs) (y :| ys) = x :| (xs ++ [y] ++ ys)

data ThisOrThat a b 
  = This a 
  | That b 
  | Both a b
  deriving (Show, Eq)

instance Semigroup (ThisOrThat a b) where
  (<>) :: ThisOrThat a b -> ThisOrThat a b -> ThisOrThat a b
  (<>) (This a)   (This _)   = This a
  (<>) (This a)   (That b)   = Both a b
  (<>) (This a)   (Both _ b) = Both a b

  (<>) (That a)   (This b)   = Both b a
  (<>) (That a)   (That _)   = That a 
  (<>) (That b)   (Both a _) = Both a b

  (<>) (Both a b) _        = Both a b   

newtype Str = Str String
  deriving (Show, Eq)

instance Semigroup Str where
  -- | Associativity concatenate on String with dot
  (<>) 
    :: Str -- ^ first given String
    -> Str -- ^ second given String
    -> Str -- ^ resulting String 
  (<>) (Str "") (Str s2) = Str s2
  (<>) (Str s1) (Str "") = Str s1
  (<>) (Str s1) (Str s2) = Str $ s1 ++ ('.' : s2)

instance Monoid Str where
  mempty :: Str
  mempty = Str ""

newtype Endo a = Endo { getEndo :: a -> a }

instance Semigroup (Endo a) where
  -- | Composition of same type functions
  (<>) :: Endo  a -> Endo a -> Endo a
  (<>) (Endo x) (Endo y) = Endo $ x . y

instance Monoid (Endo a) where
  mempty :: Endo a
  mempty = Endo id

