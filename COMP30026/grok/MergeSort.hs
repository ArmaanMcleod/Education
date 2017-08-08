{-Now that you've seen how easy it is to write a sorting algorithm in Haskell, it's your turn to try.

  Okay, merge sort takes a few more lines of code than quicksort. But you can do this!

  Write a function msort which takes a list of integers and sorts it in ascending order using a top-down merge sort strategy.

  For example:


  Main> msort [1,5,9,8,4,7,2,6,3]
  [1,2,3,4,5,6,7,8,9]
-}

msort :: [Int] -> [Int]
msort []  = []
msort [x] = [x]
msort xs  = merge (msort as) (msort bs)
    where as = take n xs
          bs = drop n xs
          n  = (length xs) `div` 2

merge :: [Int] -> [Int] -> [Int]
merge [] ys = ys
merge xs [] = xs
merge (x:xs) (y:ys)
    | x < y     = x : merge xs (y:ys)
    | otherwise = y : merge (x:xs) ys