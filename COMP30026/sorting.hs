-- quicksort
qsort :: [Int] -> [Int]
qsort [] = []
qsort (pivot:others) = (qsort lowers) ++ [pivot] ++ (qsort highers)
    where lowers = filter (<pivot) others
          highers = filter (>=pivot) others

-- mergesort
firstHalf :: [Int] -> [Int]
firstHalf xs = take(length xs `div` 2) xs

secondHalf :: [Int] -> [Int]
secondHalf xs = drop(length xs `div` 2) xs

merge :: [Int] -> [Int] -> [Int]
merge [] xs = xs
merge ys [] = ys
merge (x:xs) (y:ys)
    | (x <= y) = x:(merge xs (y:ys))
    | otherwise = y:(merge (x:xs) ys)

msort :: [Int] -> [Int]
msort [] = []
msort [x] = [x]
msort xs = merge (msort(firstHalf xs)) (msort (secondHalf xs))

-- polymorphic quicksort

qsort :: (Ord a) => [a] -> [a]
qsort [] = []
qsort (pivot:others) = (qsort lowers) ++ [pivot] ++ (qsort highers)
    where lowers = filter (<pivot) others
          highers = filter (>=pivot) others


