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