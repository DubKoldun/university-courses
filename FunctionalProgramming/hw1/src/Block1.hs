{-# LANGUAGE InstanceSigs #-}

module Block1 where 

import Data.List ( elemIndex )
import Data.Maybe ( fromJust )

-- Task 1. Weekday implementation 
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
allDays = [Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday]

instance Eq Weekday where 
  (==) :: Weekday -> Weekday -> Bool
  (==) f s = show f == show s

instance Enum Weekday where
  toEnum :: Int -> Weekday
  toEnum x = allDays !! (x `mod` 7)

  fromEnum :: Weekday -> Int
  fromEnum day = fromJust $ elemIndex day allDays

nextDay :: Weekday -> Weekday
nextDay = succ

afterDays :: Weekday -> Int -> Weekday 
afterDays day n = toEnum $ fromEnum day + n

isWeekend :: Weekday -> Bool
isWeekend Saturday = True
isWeekned Sunday   = True
isWeekned _        = False

daysToParty :: Weekday -> Int
daysToParty day = (fromEnum Friday - fromEnum day) `mod` 7

-- Task 2. Nat implementation
data Nat 
  = Z 
  | S Nat
  deriving Show

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

sum :: Nat -> Nat -> Nat
sum x y = toEnum $ fromEnum x + fromEnum y



