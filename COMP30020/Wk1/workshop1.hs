-- question 5
xor :: Bool -> Bool -> Bool
xor x y = x /= y

-- question 6
append :: [a] -> [a] -> [a]
append x [] = x
append [] y = y
append x y = x ++ y

append' :: [a] -> [a] -> [a]
append' x [] = x
append' [] y = y
append' (x: xs) ys = x : append xs ys

-- question 7
myReverse :: [a] -> [a]
myReverse [] = []
myReverse [x] = [x]
myReverse (x:xs) =  myReverse xs ++ [x]

-- question 8
getNthElem :: Int -> [a] -> a
getNthElem _ [] = error "Index too large"
getNthElem 0 (x:xs) = x
getNthElem x xs = getNthElem (n-1) xs








