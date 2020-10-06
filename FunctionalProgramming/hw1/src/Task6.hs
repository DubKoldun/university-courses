module Task6 where -- TODO()

import Data.Either (partitionEithers)

-- | Takes list of 'Maybe' with lists and concatenate that
maybeConcat 
  :: [Maybe [a]] -- given list of 'Maybe'
  -> [a] -- ^ lists contains elements from internal 'Maybe' lists
maybeConcat xs = concat $ concat <$> xs 

-- | Takes list of 'Either a b', where types 'a' and 'b'
-- implements 'Monoid' interface and returns 'Pair' of 'Monoid'
-- (elements union according to their types)
eitherConcat 
  :: (Monoid a, Monoid b) -- restriction on inner 'Either' types
  => [Either a b] -- ^ given list of 'Either'
  -> (a, b) -- ^ pair of concatenating 'Monoid' 
eitherConcat xs = (mconcat lefts, mconcat rights)
  where
    (lefts, rights) = partitionEithers xs  