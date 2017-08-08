{-Write a function freqs that takes as input an unsorted list of integers xs. 
  It should return another list of integers, representing the number of times each distinct 
  element of xs occurs. These counts should come in the same order as the sorted list of unique elements in xs.

  For example:

  Main> freqs [2,2,1,3,4,4,4]
  [1,2,1,3]
  This represents 1 occurring once, 2 occuring twice, 3 occuring once and 4 occuring 3 times.
-}

import Data.List

freqs :: [Int] -> [Int]
freqs xs = map length (group (sort xs))