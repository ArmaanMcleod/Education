{-Using your new knowledge of list functions, write a function setEq that takes two lists of integers and checks if they are made from the same set of distinct elements. If so, your function should return True. If not, then it should return False.

  For example:

  Main> setEq [1,2,3] [1,3,2]
  True
  Main> setEq [1,2,2] [2,1]
  True
  Main> setEq [1,2,3] [2,1]
  False
  Main> setEq [1,2,3] [0,1,2,3]
  False
  Main> setEq [1,2,3] [1,3,2]
  True
  Main> setEq [1,2,2] [2,1]
  True
  Main> setEq [1,2,3] [2,1]
  False
  Main> setEq [1,2,3] [0,1,2,3]
  False
-}

import Data.List

setEq :: [Int] -> [Int] -> Bool
setEq xs ys = sort (nub xs) == sort (nub ys)