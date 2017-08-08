-- Question 3
factorial :: Integer -> Integer
factorial 0 = 1
factorial n = n * factorial(n-1)

factorial' :: Integer -> Integer
factorial' n = product [1..n]

-- Question 4
-- search functions
linearsearch :: (Ord a) => a -> [a] -> Bool
linearsearch _ [] = False
linearsearch x (y:ys)
    | x == y = True
    | otherwise = linearsearch x ys

binarysearch :: (Ord a) => a -> [a] -> Bool
binarysearch _ [] = False
binarysearch x (y:ys)
    | val > x = binarysearch x (take(mid-1) ys)
    | val < x = binarysearch x (drop(mid+1) ys)
    | otherwise = True
    where mid = (length ys) `div` 2
          val = ys!!mid


myElem :: (Ord a) => a -> [a] -> Bool
myElem x ys = binarysearch x ys

-- Question 5
longestPrefix :: (Eq a) => [a] -> [a] -> [a]
longestPrefix _ [] = []
longestPrefix [] _ = []
longestPrefix (x:xs) (y:ys)
    | x == y = x : longestPrefix xs ys 
    | otherwise = []

-- Question 7
minmax :: Int -> Int -> [Int]
minmax min max = [min..max]
    




