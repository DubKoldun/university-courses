module Task5 
  (
    joinWith
  , splitOn
  ) where

import Data.List.NonEmpty (NonEmpty ((:|)), fromList)

-- | Takes list and element, 
-- and splits given list by given element (separator)
splitOn
  :: Eq a -- restriction for equalation
  => a -- ^ split elem
  -> [a] -- ^ splitting list
  -> NonEmpty [a] -- ^ list of separate blocks
splitOn sep = foldr splitByChar (fromList [[]])
  where -- TODO() problem with types
    splitByChar curElem (y :| ys) | curElem == sep = [] :| y : ys
                                  | otherwise      = (curElem : y) :| ys

-- | Takes none empty list of lists 
-- and concatenates inner list by given element
joinWith
  :: Eq a -- restriction for equalation
  => a -- ^ given joining element
  -> NonEmpty [a] -- ^ none empty list of lists
  -> [a] -- ^ the result of joining
joinWith joiner (x :| xs) = foldl joinByChar x xs
  where
    joinByChar acc y = acc ++ joiner : y