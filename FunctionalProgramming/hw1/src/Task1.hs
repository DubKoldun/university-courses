{-# LANGUAGE InstanceSigs #-}

module Task1
  ( Weekday(..)

  , afterDays
  , daysToParty
  , isWeekend
  , nextDay
  ) where

import Data.List (elemIndex)
import Data.Maybe (fromJust)

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

-- | Define a list of all 'Weekday' constructors
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

  -- | 'fromJust' used because 'elemIndex' returns Maybe,
  -- but we know that in 'fromEnum' we get one of 'Weekday' constructors,
  -- which all contains in 'allDays'
  fromEnum :: Weekday -> Int
  fromEnum day = fromJust $ elemIndex day allDays

-- | Takes 'Weekday' and returns the next
nextDay 
  :: Weekday -- ^ 'Weekday' which we give
  -> Weekday -- ^ next 'Weekday'
nextDay = succ

-- | Takes 'Weekday' and number and returns 'Weekday',
-- which follow after given number of a days
afterDays 
  :: Weekday -- ^ initial 'Weekday'
  -> Int -- ^ number of days
  -> Weekday -- ^ result 'Weekday'
afterDays day n = toEnum $ fromEnum day + n

-- | Takes a 'Weekday' and checks if the that is a weekend
isWeekend 
  :: Weekday -- ^ 'Weekday' which we need to check 
  -> Bool -- ^ result is 'True' if current day a weekend and 'False in other case
isWeekend Saturday = True
isWeekned Sunday   = True
isWeekned _        = False

-- | Takes 'Weekday' and returns amount of days til the party
daysToParty 
  :: Weekday  -- ^ 'Weekday' which we give
  -> Int -- ^ number of days until 'Friday'
daysToParty day = (fromEnum Friday - fromEnum day) `mod` 7
