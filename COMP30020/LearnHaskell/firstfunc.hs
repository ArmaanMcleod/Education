-- basic functions
doubleMe x = x + x
doubleUS x y = x*2 + y*2
doubleSmallNumber x = if x > 100 then x else x*2
doubleList xs = [if x > 10 then x else x*2 | x <- xs]

-- removes lowercase letters from string
removeNonUppercase :: [Char] -> [Char]
removeNonUppercase st = [c | c <- st, c `elem` ['A'..'Z']]

-- adds three Elements together
addThree :: Int -> Int -> Int -> Int
addThree x y z =  x + y + z

-- calculates factorial
factorial :: Integer -> Integer
factorial n = product [1..n]

-- calculates circumference
circumference :: Float -> Float
circumference r = 2 * pi * r

circumference' :: Double -> Double  
circumference' r = 2 * pi * r

-- head element of list
headElement :: [a] -> a
headElement h = head h

-- tail elements of list
tailElement :: [a] -> [a]
tailElement t = tail t

-- every element but last of list
initElement :: [a] -> [a]
initElement i = init i

-- last element of list
lastElement :: [a] -> a
lastElement l = last l


