{-# LANGUAGE InstanceSigs #-}

module Block1 where 

import Data.List ( elemIndex )
import Data.Maybe ( fromJust )

-- | Task 1. Weekday implementation 

-- | Declare type for days of the week
data Weekday 
  = Monday
  | Tuesday
  | Wednesday
  | Thursday
  | Friday
  | Saturday
  | Sunday
  deriving Show

allDays :: [Weekday]
allDays = 
  [ Monday
  , Tuesday
  , Wednesday
  , Thursday
  , Friday
  , Saturday
  , Sunday
  ]

instance Eq Weekday where 
  (==) :: Weekday -> Weekday -> Bool
  (==) f s = show f == show s

instance Enum Weekday where
  toEnum :: Int -> Weekday
  toEnum x = allDays !! (x `mod` 7)

  fromEnum :: Weekday -> Int
  fromEnum day = fromJust $ elemIndex day allDays

-- | Returns next day
nextDay :: Weekday -> Weekday
nextDay = succ

-- | Returns day after `n` days
afterDays :: Weekday -> Int -> Weekday 
afterDays day n = toEnum $ fromEnum day + n

-- | Сhecks if the current day is a weekend
isWeekend :: Weekday -> Bool
isWeekend Saturday = True
isWeekned Sunday   = True
isWeekned _        = False

-- | Returns amount of days til the party
daysToParty :: Weekday -> Int
daysToParty day = (fromEnum Friday - fromEnum day) `mod` 7

-- Task 2. Nat implementation

-- | Declare type for Nat
data Nat 
  = Z 
  | S Nat
  deriving Show

-- | Enum instance for Nat
instance Enum Nat where 
  toEnum :: Int -> Nat
  toEnum x | x < 0     = error "negative isn't natural"
           | otherwise = generate x
              where 
                generate :: Int -> Nat
                generate 0 = Z
                generate y = S (generate (y-1))

  fromEnum :: Nat -> Int
  fromEnum Z = 0
  fromEnum (S rest) = fromEnum rest + 1 

-- | Eq instance for comparsion for equality
instance Eq Nat where
  (==) :: Nat -> Nat -> Bool
  (==) x y = show x == show y

-- | Ord instance for comparsion
instance Ord Nat where
  (<=) :: Nat -> Nat -> Bool
  (<=) = toAbstractOperation (<=)

toAbstractOperation :: (Int -> Int -> t) -> Nat -> Nat -> t
toAbstractOperation f x y = fromEnum x `f` fromEnum y

toNatOperation :: (Int -> Int -> Int) -> Nat -> Nat -> Nat
toNatOperation f x y = toEnum $ toAbstractOperation f x y

-- | Returns sum of 2 Nat
sum :: Nat -> Nat -> Nat
sum = toNatOperation (+) 

-- | Returns multiplication of 2 Nat
mul :: Nat -> Nat -> Nat
mul = toNatOperation (*)

-- | Returns substraction of 2 Nat
sub :: Nat -> Nat -> Nat
sub Z     _     = Z
sub x     Z     = x
sub (S x) (S y) = sub x y 

-- | Convert Int to Nat: using Enum function
toNat :: Int -> Nat
toNat = toEnum

-- | Convert Nat to Int: using Enum function
fromNat :: Nat -> Int
fromNat = fromEnum

-- | Parity check 
isEven :: Nat -> Bool
isEven Z         = True
isEven (S Z)     = False
isEven (S (S x)) = isEven x

-- | Returns integer division
natDiv :: Nat -> Nat -> Nat
natDiv = toNatOperation div

-- | Returns modulo
natMod :: Nat -> Nat -> Nat
natMod = toNatOperation mod

-- | Task 3. Tree implementation

-- | Declare type for Binary Search Tree
data Tree a
  = Leaf
  | Branch (Tree a) [a] (Tree a)  

-- | Check tree on emptiness
isEmpty :: Tree a -> Bool
isEmpty Leaf = True
isEmpty _    = False

-- | Returns the size of list 
size :: Tree a -> Int
size Leaf            = 0
size (Branch x ys z) = length ys + size x + size z 

-- | 
contains :: Ord a => a -> Tree a -> Bool
contains elem Leaf                           = False
contains elem (Branch x (y:_) z) | y == elem = True
                                 | otherwise = if elem < y
                                               then contains elem x
                                               else contains elem z

