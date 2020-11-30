-- | Block 2 of functional programming homework
module Block2
  ( ArithmeticError(..)
  , Expression(..)

  , eval
  , moving
  ) where


import Control.Monad.State.Lazy
-- Task 1

-- | Data type for arithmetic expression
data Expression
  = Constant Int -- ^ constructor for integer constants
  | Add Expression Expression -- ^ constructor for binary addition
  | Sub Expression Expression -- ^ constructor for binary substraction
  | Mul Expression Expression -- ^ constructor for binary multiplication
  | Div Expression Expression -- ^ constructor for binary integer division
  | Pow Expression Expression -- ^ constructor for exponentiation

-- | Data type for errors that can happen
data ArithmeticError
  = NegativePow -- ^ constructor for negative power error
  | DivideByZero -- ^ constructor for division by zero
  deriving (Eq, Show)

-- | Function which evaluate given expression
eval
  :: Expression -- ^  given expression
  -> Either ArithmeticError Int -- ^ Int or error if something went wrong
eval (Constant x)      = return x
eval (Add expr1 expr2) = fmap (+) (eval expr1) <*> eval expr2
eval (Sub expr1 expr2) = fmap (-) (eval expr1) <*> eval expr2
eval (Mul expr1 expr2) = fmap (*) (eval expr1) <*> eval expr2
eval (Div expr1 expr2) =
  case eval expr2 of
    Right 0     -> Left DivideByZero
    secondValue -> fmap div (eval expr1) <*> secondValue
eval (Pow expr1 expr2) =
  case eval expr2 of
    Right x | x < 0     -> Left NegativePow
            | otherwise -> fmap (^) (eval expr1) <*> Right x
    err -> err

-- Task 2

-- | Data type for data of current state
data StepData a = StepData [a] [a] a Int Int

-- | Function that implements truncated move
truncMove :: (Fractional a) => StepData a -> StepData a
truncMove (StepData (x:xs) ys value step curStep) =
  StepData xs ys (value + x) step (curStep + 1)
truncMove _ = error "pattern matching" -- it will never happens because of 'moving' implementation

-- | Function that implements simple move
simpleMove :: (Fractional a) => StepData a -> StepData a
simpleMove (StepData (x:xs) (y:ys) value step curStep) =
  StepData xs ys (value + x - y) step curStep
simpleMove _ = error "pattern matching" -- it will never happens because of 'moving' implementation

-- | Getter for step from StepData
getStep :: (Fractional a) => StepData a -> Int
getStep (StepData _ _ _ step _) = step

-- | Getter for current step from StepData
getCurrentStep :: (Fractional a) => StepData a -> Int
getCurrentStep (StepData _ _ _ _ curStep) = curStep

-- | Getter for value from StepData
getValue :: (Fractional a) => StepData a -> a
getValue (StepData _ _ value _ _) = value

-- | Simple moving average algorithm
moveMonad :: (Fractional a) => State (StepData a) a
moveMonad = do
  step <- gets getStep
  curStep <- gets getCurrentStep
  if step /= curStep
  then modify truncMove
  else modify simpleMove
  newCurStep <- gets getCurrentStep
  value <- gets getValue
  return (value / fromIntegral newCurStep)

-- | Simple moving average algorithm implementation that use State monad
-- consumes period and list of numbers for which the Fractional instance is defined
moving
  :: (Fractional a)
  => Int -- ^ given period (step)
  -> [a] -- ^ given list of numbers
  -> [a] -- ^ resulting list
moving step lst = evalState (replicateM (length lst) moveMonad) (StepData lst lst 0 step 0)
