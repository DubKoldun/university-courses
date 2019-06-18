f :: Integer -> Integer -> Integer

f a b = a*b

main = do
  in1  <- getLine
  in2  <- getLine
  let a = (read in1 :: Integer)
  let b = (read in2 :: Integer)
  print (f a b)
