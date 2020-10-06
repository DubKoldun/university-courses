{-# LANGUAGE InstanceSigs #-}

module Task2 
  (
    Nat(..),

    fromNat,
    isEven,
    natDiv,
    natMod, 
    natMul,
    natSub,
    natSum,
    toNat
  ) where

-- | Declare type for the natrual numbers (Nat)
data Nat 
  = Z 
  | S Nat
  deriving Show

-- | Enum instance for Nat
instance Enum Nat where
  toEnum :: Int -> Nat
  toEnum n | n < 0     = generate 0
           | otherwise = generate n  
    where
      generate :: Int -> Nat
      generate 0 = Z
      generate x = S (generate (x-1))

  fromEnum :: Nat -> Int
  fromEnum Z = 0
  fromEnum (S rest) = fromEnum rest + 1 

-- | Eq instance for comparsion for equality
instance Eq Nat where
  (==) :: Nat -> Nat -> Bool
  (==) = toAbstractOperation (==)

-- | Ord instance for comparsion
instance Ord Nat where
  (<=) :: Nat -> Nat -> Bool
  (<=) = toAbstractOperation (<=)

-- | Takes function of two 'Int' and apply to 'Nat'
toAbstractOperation 
  :: (Int -> Int -> t) -> Nat -> Nat -> t
toAbstractOperation f x y = fromEnum x `f` fromEnum y

-- | Takes function of two 'Int' and apply to 'Nat'
-- also convert result to 'Nat'
toNatOperation :: (Int -> Int -> Int) -> Nat -> Nat -> Nat
toNatOperation f x y = toEnum $ toAbstractOperation f x y

-- | Takes 2 'Nat' and returns their sum 
natSum :: Nat -> Nat -> Nat
natSum = toNatOperation (+) 

-- | Takes 2 'Nat' and returns their multiplication 
natMul :: Nat -> Nat -> Nat
natMul = toNatOperation (*)

-- | Takes 2 'Nat' and returns their substraction 
natSub :: Nat -> Nat -> Nat
natSub Z     _     = Z
natSub x     Z     = x
natSub (S x) (S y) = natSub x y 

-- | Convert Int to Nat 
-- (using Enum function implementation)
toNat :: Int -> Nat
toNat = toEnum

-- | Convert Nat to Int 
-- (using Enum function implementation)
fromNat :: Nat -> Int
fromNat = fromEnum

-- | Takes 'Nat' and checks on parity 
isEven 
  :: Nat -- ^ given 'Nat'
  -> Bool -- ^ 'True' if even else 'False'
isEven Z         = True
isEven (S Z)     = False
isEven (S (S x)) = isEven x

-- | Returns integer division
natDiv :: Nat -> Nat -> Nat
natDiv = toNatOperation div

-- | Returns modulo
natMod :: Nat -> Nat -> Nat
natMod = toNatOperation mod
