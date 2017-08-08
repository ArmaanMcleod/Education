{-To practice your skills with lists, write a function evens that takes an integer n and generates a list 
  of the first n positive even integers (starting with 2).

  For example:

  Main> evens 0
  []
  Main> evens 1
  [2]
  Main> evens 3
  [2,4,6]
  Main> evens 6
  [2,4,6,8,10,12]
-}

evens :: Int -> [Int]
evens n = [2,4..2*n]