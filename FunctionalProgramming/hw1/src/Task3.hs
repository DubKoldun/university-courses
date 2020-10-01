{-# LANGUAGE InstanceSigs #-}

module Task3 where -- TODO()

-- | Declare type for Binary Search Tree
data Tree a
  = Leaf
  | Branch (Tree a) [a] (Tree a)  

instance (Ord a) => Eq (Tree a) where
  (==) :: (Ord a) => Tree a -> Tree a -> Bool
  (==) Leaf Leaf = True
  (==) (Branch l1 xs r1) (Branch l2 ys r2) = 
    case compare ys xs of
      EQ -> l1 == l2 && r1 == r2
      _  -> False
  (==) _ _ = False 

-- instance (Ord a) => Ord (Tree a) where

-- | 
isEmpty 
  :: Ord a 
  => Tree a 
  -> Bool
isEmpty Leaf = True
isEmpty _    = False

-- | Returns the size of list 
size 
  :: Ord a
  => Tree a 
  -> Int
size Leaf                   = 0
size (Branch left xs right) = length xs + size left + size right 

-- | Check on containing element in tree
contains 
  :: Ord a 
  => Tree a 
  -> a
  -> Bool
contains Leaf _ = False
contains (Branch left (x:_) right) el = 
  case compare el x of
    EQ -> True
    LT -> contains left  el
    GT -> contains right el
contains (Branch _ [] _) _ = error "Tree doesn't have the required structure"

insert
  :: Ord a
  => Tree a
  -> a
  -> Tree a
insert = undefined
