module Main where

import Control.Applicative (ZipList(..))

-- Ноль
-- Z: N_0 -> N_0, Z(x) = 0
z :: [Int] -> Int
z _ = 0

--Инкремент
-- N: N_0 -> N_0, N(x) = x + 1
n :: [Int] -> Int
n [x] = x + 1

-- Проекция
-- U_i^n: N_0^n -> N_0, U_i^n(x1,...,x_n) = x_i
u :: Int -> [Int] -> Int
u _ []     = -1
u 1 (x:_)  = x
u i (x:xs) = u (i-1) xs

-- Подстановка
-- (f: N_0^n -> N_0) и (g_1,...g_n: N_0^m -> N_0), то (S{f,g_1,...,g_n}: N_0^m -> N_0). При этом (S{f,g_1,...,g_n}(x_1,...x_n) = f(g(x_1,...,x_n),...,g(x_1,...,x_n)))
s f gs args = f (getZipList $ ZipList gs <*> pure args)

sr f gs args = f (init buff, last buff) where
    buff = getZipList $ ZipList gs <*> pure args

-- Рекурсия
-- (f: N_0^n -> N_0) и (g: N_0^(n+2) -> N_0), то (R{f,g}: N_0^(n+1), при этом R{f,g}(x_1,...,x_n,y) = {f(x_1,...,x_n), y = 0 | g(x_1,...,x_n,y-1,R{f,g}(x_1,...,x_n,y-1))}
r (f, _, (xs,0)) = f xs
r (f, g, (xs,y)) = g (xs ++ [y-1, r (f, g, (xs, y-1))])

--hs pow prod plus
plushs :: [Int] -> Int
plushs args = (+) (u 1 args) (u 2 args)

prodhs :: [Int] -> Int
prodhs args = (*) (u 1 args) (u 2 args)

prod10hs :: [Int] -> Int
prod10hs args = (*) (u 1 args) 10

powhs :: [Int] -> Int
powhs args = (^) (u 1 args) (u 2 args)

subhs :: [Int] -> Int
subhs args = (-) (u 1 args) (u 2 args)

modhs :: [Int] -> Int
modhs args = mod (u 1 args) (u 2 args)

divhs :: [Int] -> Int
divhs args = div (u 1 args) (u 2 args)

div2hs :: [Int] -> Int
div2hs args = div (u 1 args) 2

div10hs :: [Int] -> Int
div10hs args = div (u 1 args) 10

--one
one :: [Int] -> Int
one = s n [s z [u 1]]

--two
two :: [Int] -> Int
two = s n [s n [s z [u 1]]]

--ten
ten args = s constant [u 2] (args ++ [10])

--constant
constf :: [Int] -> Int
constf = s z [u 1]

constg :: [Int] -> Int
constg = s n [u 3] 

constant :: [Int] -> Int
constant = sr (r . (,,) constf constg) [u 1, u 1]

--plus 1a
plusf :: [Int] -> Int
plusf = u 1

plusg :: [Int] -> Int
plusg = s n [u 3] 

plus :: [Int] -> Int
plus = sr (r . (,,) plusf plusg) [u 1, u 2]

--prod 1b
prodf :: [Int] -> Int
prodf = s z [u 1]

prodg :: [Int] -> Int
prodg = s plus [u 1, u 3]

prod :: [Int] -> Int
prod = sr (r . (,,) z prodg) [u 1, u 2]

--sub1 1c
sub1g :: [Int] -> Int
sub1g = u 2

sub1' :: [Int] -> Int
sub1' = sr (r . (,,) z sub1g) [u 1, u 2]

sub1 :: [Int] -> Int
sub1 = s sub1' [u 1, u 1]

--sub 1d
subf :: [Int] -> Int
subf = u 1

subg :: [Int] -> Int
subg = s sub1 [u 3]

sub :: [Int] -> Int
sub = sr (r . (,,) subf subg) [u 1, u 2]

--lower 1e
lowerf :: [Int] -> Int
lowerf = s n [z]

lowerg :: [Int] -> Int
lowerg = s z [u 1]

lower :: [Int] -> Int
lower = sr (r . (,,) lowerf lowerg) [s sub [s plus [u 1, one], u 2], s sub [s plus [u 1, one], u 2]]

--if'
ifh :: [Int] -> Int
ifh = u 2

ifg :: [Int] -> Int
ifg = u 1

if' :: [Int] -> Int
if' = sr (r . (,,) ifh ifg) [u 2, u 3, u 1]

--byteAnd 1f

-- byteXor 1g

--div2
div2g :: [Int] -> Int
div2g = s if' [s lower [s sub [u 1, s prod [u 3, two]], two], u 3, s plus [u 3, one]]

div2 :: [Int] -> Int
div2 = sr (r . (,,) z div2g) [u 1, u 1]

-- -- first 1h
-- firstf :: ([Int] -> Int) -> [Int] -> Int
-- firstf f  = f 

-- firstg :: [Int] -> Int
-- firstg = u 1

-- first :: ([Int] -> Int) -> [Int] -> Int
-- first f args = r (s f, firstg, args)

--div 1i
divf :: [Int] -> Int
divf = s z [u 1]

divg :: [Int] -> Int
divg = s if' [s lower [s sub [u 1, s prod [u 4, u 2]], u 2], u 4, s plus [u 4, one]]

div' :: [Int] -> Int
div' = sr (r . (,,) divf divg) [u 1, u 2, u 1]

--mod 1j
mod' :: [Int] -> Int
mod' = s sub [u 1, s prod [u 2, s div' [u 1, u 2]]]

--pow 1k
powf :: [Int] -> Int
powf = s n [z]

powg :: [Int] -> Int
powg = s prod [u 1, u 3]

pow :: [Int] -> Int
pow = sr (r . (,,) powf powg) [u 1, u 2]

--plogk 1l
--div2while0
div2while0h :: [Int] -> Int
div2while0h = s if' [s eq [s div2 [u 1], z], u 2, s div2while0' [s div2 [u 1], s plus [u 2, one], z]]

div2while0' :: [Int] -> Int
div2while0' = sr (r . (,,) div2while0h z) [u 1, u 2, z]

div2while0 :: [Int] -> Int
div2while0 = s div2while0' [u 1, one]


plogkh :: [Int] -> Int
plogkh = s z [u 1]

plogkg :: [Int] -> Int
plogkg = s if' [s eq [s modhs [u 1, s powhs [u 2, u 3]], z], u 3, u 4]

plogk :: [Int] -> Int
plogk = sr (r . (,,) plogkh plogkg) [u 1, u 2, s plus [ s div2while0 [u 1], one]]

--fac 1m
facf :: [Int] -> Int
facf = s n [z]

facg :: [Int] -> Int
facg = s prod [s n [u 2], u 3]

fac' :: [Int] -> Int
fac' = sr (r . (,,) facf facg) [u 1, u 2]

fac :: [Int] -> Int
fac = s fac' [u 1, u 1]

--pair 1n

--isPrime 1o
--eq
eq :: [Int] -> Int
eq = s if' [s lower [u 1, u 2], z, s if' [s lower [u 2, u 1], z, one]]

primef :: [Int] -> Int
primef = s z [u 1]

primeg :: [Int] -> Int
primeg = s if' [s eq [u 2, one], one, s if' [s modhs [u 1, u 2], s prodhs [one, u 3], z]]

prime :: [Int] -> Int
prime = sr (r . (,,) primef primeg) [u 1, u 1]

--primek 1p
--nextPrime
nextPrimef :: [Int] -> Int
nextPrimef = s if' [s eq [s prime [u 1], z], s nextPrime [s plushs [one, u 1]], u 1]

nextPrime :: [Int] -> Int
nextPrime = sr (r . (,,) nextPrimef z) [u 1, z]

primekf :: [Int] -> Int
primekf = one

primekg :: [Int] -> Int
primekg = s nextPrime [s plushs [u 3, one]]

primek :: [Int] -> Int
primek = sr (r . (,,) primekf primekg) [u 1, u 1]

--nil 2a (в чатике Штукен написал)
nil :: [Int] -> Int
nil = one

--cons 2b
--Новый Список, Старый Список, позиция в старом
consf :: [Int] -> Int
consf = s if' [s eq [s getk [u 2, u 3], z], u 1, s prodhs [u 1, s cons' [s powhs [s primek [s plushs [u 3, one]], s getk [u 2, u 3]], u 2, s plushs [u 3, one]]]]

cons' :: [Int] -> Int
cons' = sr (r . (,,) consf z) [u 1, u 2, u 3, z]

cons :: [Int] -> Int
cons = s cons' [s powhs [two, u 1], u 2, one]

--head 2c
headh :: [Int] -> Int
headh = s if' [s modhs [u 1, two], z, s plushs [one, s head' [s divhs [u 1, two]]]]

head' :: [Int] -> Int
head' = sr (r . (,,) headh z) [u 1, z]

--tail 2d
tailf :: [Int] -> Int
tailf = s if' [s eq [s getk [u 2, u 3], z], u 1, s prodhs [u 1, s tailf' [s powhs [s primek [s sub [u 3, one]], s getk [u 2, u 3]], u 2, s plushs [u 3, one]]]]

tailf' = sr (r . (,,) tailf z) [u 1, u 2, u 3, z]

tail' = s tailf' [one, u 1, two]

--getk 2e
getkf :: [Int] -> Int
getkf = s if' [s modhs [u 1, u 2],z,s plushs [one, s getk [s divhs [u 1, u 2], u 3]]]

getk = s if' [s eq [u 1, z],z, sr (r . (,,) getkf z) [u 1, s primek [u 2],u 2, z]]

--len 2f

len'f :: [Int] -> Int
len'f = s if' [s modhs [u 1, s primek [u 2]],z, s plushs [one, s len' [u 1, s plushs [one,u 2]]]]

len' = sr (r . (,,) len'f z) [u 1,u 2, z]

len = s if' [s eq [u 1, z], z, s len' [u 1, one]]

--concat 2g
--Список а, Новый список, len 1 списка, позиция в 1 списке
concatf = s cons [s getk [u 1, u 3], u 2]

concatg = s cons [s getk [u 1, s sub [u 3, s plus [u 4, one]]], u 5]

concat' = sr (r . (,,) concatf concatg) [u 1, u 2, s len [u 1], s sub [s len [u 1], one]]


main = do
putStr . show $ concat' [2,6]
putStr . show $ concat' [2,4]
putStr . show $ concat' [2,2]
