{-# LANGUAGE InstanceSigs #-}

module Task3
  ( 
    Tree(..)

  , contains
  , fromList
  , insert
  , isEmpty
  , remove
  , size
  , Task3.toList
  ) where


import Data.List.NonEmpty (NonEmpty((:|)), toList)

-- | Declare type for Binary Search Tree
data Tree a
  = Leaf
  | Branch (Tree a) (NonEmpty a) (Tree a)  
  deriving Show

instance (Ord a) => Eq (Tree a) where
  (==) :: (Ord a) => Tree a -> Tree a -> Bool
  (==) Leaf Leaf = True
  (==) (Branch l1 xs r1) (Branch l2 ys r2) = 
    case compare ys xs of
      EQ -> l1 == l2 && r1 == r2
      _  -> False
  (==) _ _ = False 

-- | Takes 'Tree' and checks on emptiness
isEmpty
  :: Tree a -- ^ given 'Tree'
  -> Bool -- if 'Tree' is empty returns 'True' else 'False'
isEmpty Leaf = True
isEmpty _    = False

-- | Returns the size of list 
size 
  :: Tree a -- ^ given 'Tree'
  -> Int -- ^ resulting size
size Leaf                   = 0
size (Branch left xs right) = length xs + size left + size right 

-- | Check on containing elent in tree
contains 
  :: Ord a -- restriction for BST correctness
  => Tree a  -- ^ given 'Tree'
  -> a -- ^ element which we find
  -> Bool -- ^ return 'True' if elem contain in 'Tree'
contains Leaf _ = False
contains (Branch left (x :| _) right) el = 
  case compare el x of
    EQ -> True
    LT -> contains left  el
    GT -> contains right el

-- | Inserts element in 'Tree'
insert
  :: Ord a --  restriction for BST correctness
  => Tree a -- ^ given 'Tree'
  -> a -- ^ element which we need to insert
  -> Tree a -- ^ resulting 'Tree'
insert Leaf el = Branch Leaf  (el :| []) Leaf
insert (Branch l xs@(x :| _) r) el = 
  case compare el x of
    EQ -> Branch l (el :| Data.List.NonEmpty.toList xs) r
    LT -> Branch (insert l el) xs r
    GT -> Branch l xs (insert r el)

-- | Converts list to 'Tree'
fromList
  :: Ord a -- restriction for BST correctness
  => [a] -- ^ given list
  -> Tree a -- ^ resulting BST 'Tree'
fromList xs = generate xs Leaf
  where
    generate :: Ord a => [a] -> Tree a -> Tree a
    generate []       tree = tree
    generate (y : ys) tree = generate ys (insert tree y) 

-- | Removes given value from 'Tree'
remove 
  :: Ord a -- restriction for BST correctness
  => Tree a -- ^ given Tree
  -> a -- ^ element which need to remove
  -> Tree a -- ^ resulting Tree
remove Leaf _ = Leaf 
remove tree@(Branch l list@(x :| _) r) el =
  case compare el x of
    LT -> Branch (remove l el) list r         
    GT -> Branch l             list (remove r el)
    EQ -> removeFromBranch tree el                 
      where 
        removeFromBranch :: Ord a => Tree a -> a -> Tree a  
         -- never happens because we pattern matching element in previous case
        removeFromBranch Leaf                         _ = undefined             
        removeFromBranch (Branch l4 (_ :| y : ys) r4) _ = Branch l4 (y :| ys) r4 
        removeFromBranch (Branch l4 (_ :| []) r4)     _ =                        
          case r4 of
            Leaf -> l4   -- right branch is empty
            _    -> Branch l4 newValue newRight
              where 
                (newValue, newRight) = walker r4

                walker :: Ord a => Tree a -> (NonEmpty a, Tree a)
                -- never happens, because we check that in previous case
                walker Leaf = undefined                  
                -- if left is empty then return current value and branch  
                walker (Branch Leaf list2 r2) =  (list2, r2)        
                -- if inner inner left is a Leaf then rebuild tree in that order:
                -- right branch hang on the left and save order in others branches
                walker (Branch (Branch Leaf list3 r3) list2 r2) = (list3, Branch r3 list2 r2)
                -- in other case needs to continue walk in depth and hang on the
                -- left builded tree , because we rebuild this in recursion (prev pattern matching)
                walker (Branch l2 list2 r2) = (innerList, Branch leftK list2 r2)
                  where 
                    (innerList, leftK) = walker l2


-------------------------------------------------------------------------------------------------
------------------------------------------Task 4-------------------------------------------------
-------------------------------------instance Foldable-------------------------------------------
-------------------------------------------------------------------------------------------------

instance Foldable Tree where

  -- | foldr implementation for 'Tree'
  -- (right folding)
  foldr 
    :: (a -> b -> b) -- ^ folding function
    -> b -- ^ initial value
    -> Tree a -- ^ given 'Tree'
    -> b -- ^ result of folding
  foldr _ ini Leaf = ini
  foldr f ini (Branch l xs r) = foldr f (foldr f conv xs) l
    where
      -- | Continues calculate 'foldr' inorder
      conv = foldr f ini r

  -- | foldMap implementation for tree
  -- (mapping all elements of 'Tree' to 'Monoid')
  foldMap 
    :: Monoid m -- restriction on type for combine elements
    => (a -> m) -- ^ function which convert inner 'Tree' type to 'Monoid'
    -> Tree a  -- ^ given 'Tree'
    -> m  -- ^ 'Monoid's result
  foldMap f = foldr (mappend . f) mempty

-- | Takes a 'Tree' and convert to list
toList
  :: (Ord a) -- restriction for correct BST implementation 
  => Tree a -- ^ given 'Tree'
  -> [a] -- ^ result list
toList = foldr (:) []