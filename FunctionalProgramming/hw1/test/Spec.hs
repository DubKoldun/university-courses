module Spec where 

import Test.Tasty (defaultMain, testGroup)

import SpecTask1 (task1Test)
import SpecTask2 (task2Test)
import SpecTask3 (task3Test)
import SpecTask4 (task4Test)
import SpecTask5 (task5Test)
import SpecTask6 (task6Test)
import SpecTask7 (task7Test)

main :: IO ()
main = do
  unitTests1 <- task1Test 
  unitTests2 <- task2Test 
  unitTests3 <- task3Test
  untiTests4 <- task4Test
  unitTests5 <- task5Test
  unitTests6 <- task6Test
  unitTests7 <- task7Test
  let allTests = testGroup "Homework 1" [ unitTests1, unitTests2, unitTests3, untiTests4, unitTests5, unitTests6, unitTests7 ]
    in defaultMain allTests