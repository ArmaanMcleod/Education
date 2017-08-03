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