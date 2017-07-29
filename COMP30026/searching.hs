-- linear search
search :: Int -> [Int] -> Bool
search _ [] = False
search x (y:ys)
    | x == y = True
    | otherwise = search x ys

-- binary search
bsearch :: Int -> [Int] -> Bool
bsearch _ [] = False
bsearch x ys
    | val > x = bsearch x (take(mid-1) ys)
    | val < x = bsearch x (drop(mid+1) ys)
    | otherwise = True
    where mid = (length ys) `div` 2
          val = ys!!mid
    
-- all search
evn :: Int -> Bool
evn x = x `mod` 2 == 0

big :: Int -> Bool
big x = x > 100

allsearch :: (Int -> Bool) -> [Int] -> [Int]
allsearch _ [] = []
allsearch tst (x:xs)
    | tst x = [y | y <- (x:xs), tst y]
    | otherwise = allsearch tst xs