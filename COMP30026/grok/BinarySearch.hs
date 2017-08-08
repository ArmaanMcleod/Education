{-With your newfound knowledge of list functions and operations, 
  write a function bsearch which uses the idea of binary search to check 
  if an integer x occurs in a sorted list of integers ys. Your function 
  should evaluate to True if x occurs in ys, and False otherwise.

  For example:

  Main> bsearch 3 [1,2,3,5]
  True
  Main> bsearch 4 [1,2,3,5]
  False
  Main> bsearch 3 [1,2,3,5]
  True
  Main> bsearch 4 [1,2,3,5]
  False
-}

bsearch :: Int -> [Int] -> Bool
bsearch x [] = False
bsearch x ys
    | x  < mid = bsearch x (take m ys)
    | x == mid = True
    | x  > mid = bsearch x (drop (m+1) ys)
    where m = (length ys) `div` 2
          mid = ys !! m