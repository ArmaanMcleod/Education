-- question 5
xor :: Bool -> Bool -> Bool
xor x y = x /= y

-- question 6
append :: [a] -> [a] -> [a]
append x [] = x
append [] y = y
append x y = x ++ y

-- question 7
myReverse :: [a] -> [a]
myReverse [] = []
myReverse [x] = [x]
myReverse (x:xs) =  myReverse xs ++ [x]

-- question 8
getNthElem :: Int -> [a] -> a
getNthElem x xs = xs !! (x-1)








