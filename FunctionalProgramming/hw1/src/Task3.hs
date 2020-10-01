module Task3 where

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

-- | Check on containing element in tree
contains :: Ord a => a -> Tree a -> Bool
contains elem Leaf                           = False
contains elem (Branch x (y:_) z) | y == elem = True
                                 | otherwise = if elem < y
                                               then contains elem x
                                               else contains elem z

