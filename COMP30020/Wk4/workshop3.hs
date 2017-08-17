-- Question 2
ftoc :: Double -> Double
ftoc f = ((5 * 1.0) / 9) * (f - 32)

-- Question 3
quadRoots :: Double -> Double -> Double -> [Double]
quadRoots a b c = [x1, x2]
    where
      x1 = (-b + ((b^2) - 4 * a * c) * 1.0) / 2 * a
      x2 = (-b - ((b^2) - 4 * a * c) * 1.0) / 2 * a

-- Question 4
merge :: (Ord a) => [a] -> [a] -> [a]WW
merge [] [] = []
merge [] xs = xs
merge ys [] = ys
merge (x:xs) (y:ys)
    | x <= y = x : merge xs  (y:ys)
    | otherwise = y : merge (x:xs) ys

-- Question 5
qsort :: (Ord a) => [a] -> [a]
qsort [] = []
qsort (pivot:others) = qsort(lowers) ++ [pivot] ++ qsort(highers)
    where lowers = filter (<pivot) others
          highers = filter (>=pivot) others

-- Question 6
