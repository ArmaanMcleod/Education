{-Now it's your turn. Let's implement a new function allsearch which takes a function tst :: Int -> Bool and a 
  list xs :: [Int] and returns a new list with all the elements from xs for which tst returns True.

  For example, using the helper functions from earlier:

  Main> allsearch evn [1,2,3,5]
  [2]
  Main> allsearch evn [1,2,3,4,5,6]
  [2,4,6]
  Main> allsearch big [1..105]
  [101,102,103,104,105]
  Main> allsearch big [1..100]
  []
  Main> allsearch evn [1,2,3,5]
  [2]
  Main> allsearch evn [1,2,3,4,5,6]
  [2,4,6]
  Main> allsearch big [1..105]
  [101,102,103,104,105]
  Main> allsearch big [1..100]
  []
-}


allsearch :: (Int -> Bool) -> [Int] -> [Int]
allsearch tst [] = []
allsearch tst (x:xs)
    | tst x     = x:allsearch tst xs
    | otherwise =   allsearch tst xs


-- helper functions:

evn :: Int -> Bool
evn x = x `mod` 2 == 0

big :: Int -> Bool
big x = x > 100