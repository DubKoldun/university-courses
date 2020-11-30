{-# LANGUAGE InstanceSigs        #-}
{-# LANGUAGE LambdaCase          #-}
{-# LANGUAGE ScopedTypeVariables #-}

-- | Block 3 of functional programming homework
module Block3 where

import Control.Applicative (Alternative, empty, many, some, (<|>))
import Data.Bifunctor (first)
import Data.Char (isDigit)

-- Task 1. Parser instances

-- | Parser which can work with any data stream
newtype Parser s a = Parser { runParser :: [s] -> Maybe (a, [s]) }

instance Functor (Parser s) where
  fmap :: (a -> b) -> Parser s a -> Parser s b
  fmap f (Parser parser) = Parser (fmap (first f) . parser)

instance Applicative (Parser s) where
  pure :: a -> Parser s a
  pure a = Parser (\s -> Just (a, s))

  (<*>) :: forall a b. Parser s (a -> b) -> Parser s a -> Parser s b
  (Parser f) <*> (Parser v) = Parser applyF
    where
      applyF :: [s] -> Maybe (b, [s])
      applyF str = do
          (f', str') <- f str
          (a, str'') <- v str'
          return (f' a, str'')

instance Alternative (Parser s) where
  empty :: Parser s a
  empty = Parser (const Nothing)

  (<|>) :: Parser s a -> Parser s a -> Parser s a
  x <|> y = Parser $ \s ->
    case runParser x s of
      Nothing -> runParser y s
      ans     -> ans

instance Monad (Parser s) where
  return = pure

  (>>=) :: Parser s a -> (a -> Parser s b) -> Parser s b
  Parser p >>= f = Parser $ \s ->
    case p s of
      Nothing     -> Nothing
      Just (a, r) -> runParser (f a) r


-- Task 2. Useful combinators

-- | Parser that always succeeds without consuming any input
ok :: Parser s ()
ok = Parser $ \s -> Just ((), s)

-- | Parser that succeeds only at the end of input stream
eof :: Parser s ()
eof = Parser $ \case
    [] -> Just ((), [])
    _  -> Nothing

-- | Function consumes predicate and returns
-- Parser that consumes only single character
-- and returns it if predicate is true
satisfy
  :: (s -> Bool) -- ^ given predicate
  -> Parser s s -- ^ parser type
satisfy p = Parser $ \case
    []     -> Nothing
    (x:xs) -> if p x then Just (x, xs) else Nothing

-- | Function consumes one stream element and returns
-- Parser with this element to process.
element
  :: Eq s
  => s -- ^ given element
  -> Parser s s -- ^ parser type
element c = satisfy (== c)

-- | Function that consumes list of elements and returns
-- Parser thar process this list
stream
  :: Eq s
  => [s] -- ^ given list
  -> Parser s [s] -- parser type
stream = traverse element

-- Task 3. Simple parsers

-- | Parser that processes balanced brackets sequence,
-- returns Nothing if the sequence is unbalanced
correctBracketSequence :: Parser Char ()
correctBracketSequence = parser *> eof
  where
    parser :: Parser Char [Char]
    parser = many $ element '(' *> parser *> element ')'

-- | Parser thar processes integer value with optional
-- sign: "-" or "+", returns Nothing if integer can't
-- be parsed
integer :: Parser Char Int
integer = value <|> signF <*> value
  where
    value :: Parser Char Int
    value = read <$> some (satisfy isDigit)

    signF :: Parser Char (Int -> Int)
    signF = negate <$ element '-'  <|> id <$ element '+'

-- Task 4. Difficult parser ???











