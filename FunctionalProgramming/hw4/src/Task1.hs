{-# LANGUAGE BangPatterns #-}

-- | Task 1 of functional programming homework. Geometry.
module Task1
  ( Point(..)

  , crossProduct
  , doubleArea
  , doubleAreaSlow
  , minus
  , perimeter
  , perimeterSlow
  , plus
  , scalarProduct
  ) where

import Data.Foldable()

-- | Point in double dimension
data Point =
  Point
    { x :: !Int -- ^ x-axis
    , y :: !Int -- ^ y-axis
    }
  deriving (Eq, Show)


-- | Calculates sum of two 'Point'
plus
  :: Point -- ^ first given 'Point'
  -> Point -- ^ second given 'Point'
  -> Point -- ^ result 'Point'
Point x1 y1 `plus` Point x2 y2 = Point (x1 + x2) (y1 + y2)

-- | Calculates difference of two 'Point'
minus
  :: Point -- ^ first given 'Point'
  -> Point -- ^ second given 'Point'
  -> Point -- ^ result 'Point'
Point x1 y1 `minus` Point x2 y2 = Point (x1 - x2) (y1 - y2)

-- | Calculates scalar production of two 'Point'
scalarProduct
  :: Point -- ^ first given 'Point'
  -> Point -- ^ second given 'Point'
  -> Int -- ^ result 'Int'
Point x1 y1 `scalarProduct` Point x2 y2 = x1 * x2 + y1 * y2

-- | Calculates cross produciton of two 'Point'
crossProduct
  :: Point -- ^ first given 'Point'
  -> Point -- ^ second given 'Point'
  -> Int -- ^ result 'Int'
Point x1 y1 `crossProduct` Point x2 y2 = x1 * x2 - y1 * y2

-- | Calculates distance between two 'Point'.
distance
  :: Point  -- ^ first point
  -> Point  -- ^ second point
  -> Double -- ^ result 'Double'
distance p1 p2 = sqrt . fromIntegral $ scalarProduct dif dif
  where
    dif :: Point
    dif = minus p1 p2

{- | Help function that applies given function of two 'Point' and
 returns sum of accumalator and function result
-}
funcWithAcc
  :: Num a
  => (Point -> Point -> a) -- ^ given function to be applied to 'Point's
  -> a -- ^ accumulator
  -> Point -- ^ first give point
  -> Point -- ^ second given point
  -> a -- ^ result
funcWithAcc func acc p1 p2 = acc + func p1 p2

{- | Folds polygon that represented as list of 'Point's by given function
Fast implementation with strict accumulator
-}
polygonFoldFast
  :: Num a
  => (Point -> Point -> a) -- ^ given function to be applied to 'Point's
  -> Point -- ^ start 'Point'
  -> a -- ^ accumulator
  -> [Point] -- ^ polygon that contains all 'Point's (include start)
  -> a -- result
polygonFoldFast _ _ _ [] = error "Polygon fold funciton applied to incorrect polygon (fast)"
polygonFoldFast func start !acc [endP] | start == endP = error "Polygon cannot consist of one point or two same points"
                                       | otherwise = funcWithAcc func acc start endP
polygonFoldFast func start !acc (z1:fTail@(z2:_)) = polygonFoldFast func start (funcWithAcc func acc z1 z2) fTail

{- | Folds polygon that represented as list of 'Point's by given function
Slow implementation without strict accumulator
-}
polygonFoldSlow
  :: Num a
  => (Point -> Point -> a) -- ^ given function to be applied to 'Point's
  -> Point -- ^ start 'Point'
  -> a -- ^ accumulator
  -> [Point] -- ^ polygon that contains all 'Point's (include start)
  -> a -- result
polygonFoldSlow _ _ _ [] = error "Polygon fold funciton applied to incorrect polygon (slow)"
polygonFoldSlow func start acc [endP] | start == endP = error "Polygon cannot consist of one point or two same points"
                                      | otherwise = funcWithAcc func acc start endP
polygonFoldSlow func start acc (z1:fTail@(z2:_)) = polygonFoldSlow func start (funcWithAcc func acc z1 z2) fTail


{- | Calculates perimeter of given polygon 2-d (list of 'Point'),
the vertices ('Point's) of the polygon are in counterclockwise order.
Fast implementation with strict accumulator
-}
perimeter
  :: [Point] -- ^ given list of 'Point'
  -> Double -- ^ result 'Double'
perimeter [] = error "There must be points in the polygon"
perimeter lst@(p:_) = polygonFoldFast distance p 0 lst

{- | Calculates perimeter of given polygon 2-d (list of 'Point'),
the vertices ('Point's) of the polygon are in counterclockwise order.
Slow implementation without strict accumulator
-}
perimeterSlow
  :: [Point] -- ^ given list of 'Point'
  -> Double -- ^ result 'Double'
perimeterSlow [] = error "There must be points in the polygon"
perimeterSlow lst@(p:_) = polygonFoldSlow distance p 0 lst


{- | Calculates area of given polygon 2-d (list of 'Point'),
the vertices ('Point's) of the polygon are in counterclockwise order.
Fast implementation with strict accumulator
-}
doubleArea
  :: [Point] -- ^ given list of 'Point'
  -> Int -- ^ result 'Double'
doubleArea [] = error "There must be points in the polygon"
doubleArea lst@(p:_) = polygonFoldFast crossProduct p 0 lst

{- | Calculates area of given polygon 2-d (list of 'Point'),
the vertices ('Point's) of the polygon are in counterclockwise order.
Slow implementation without strict accumulator
-}
doubleAreaSlow
  :: [Point] -- ^ given list of 'Point'
  -> Int -- ^ result 'Double'
doubleAreaSlow [] = error "There must be points in the polygon"
doubleAreaSlow lst@(p:_) = polygonFoldSlow crossProduct p 0 lst
