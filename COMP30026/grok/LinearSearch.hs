{-Write a function search which takes an integer x and a list ys and returns True if x 
  occurs at least once in ys, and False otherwise.

  For example:


  Main> search 3 [1,2,3,4]
  True
  Main> search 5 [1,2,3,4]
  False
-}

search :: Int -> [Int] -> Bool
search x [] = False
search x (y:ys)
    | x == y    = True
    | otherwise = search x ys