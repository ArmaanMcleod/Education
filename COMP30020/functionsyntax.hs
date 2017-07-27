-- pattern matching
lucky :: (Integral a) => a -> String
lucky 7 = "LUCKY NUMBER SEVEN!"
lucky x = "Sorry, you're out of luck, pal!"

sayMe :: (Integral a) => a -> String
sayMe 1 = "One!"
sayMe 2 = "Two!"
sayMe 3 = "Three!"
sayMe 4 = "Four!"
sayMe 5 = "Five!"
sayMe x = "Not between 1 and 5"

-- factorial recursion
factorial :: (Integral a) => a -> a -- or Int -> Int
-- base case
factorial 0 = 1
-- recursive case
factorial n = n * factorial (n-1)

-- character matching
charName :: Char -> String
charName 'a' = "Albert"
charName 'b' = "Bob"
charName 'c' = "Cecil"
charName x = "Other"

-- adding vectors
addVectors :: (Num a) => (a, a) -> (a, a) -> (a, a)
addVectors a b = (fst a + fst b, snd a + snd b)
-- Or addVectors (x1, y1) (x2, y2) = (x1 + x2, y1 + y2)

-- getting first element tuple
first :: (a, b, c) -> a
first (x, _, _) = x

-- summing tuples in a list
listMatch :: (Num a) => [(a, a)] -> [a]
listMatch xs = [a+b | (a,b) <- xs]

-- new head function
head' :: [a] -> a
head' [] = error "Can't call head on an empty list!"
head' (x:_) = x

-- show first elements in a list
tell :: (Show a) => [a] -> String
tell [] = "The list is empty"
tell (x:[]) = "The list has one element: " ++ show x
tell (x:y:[]) = "The list had two elements: " ++ show x ++ " and " ++ show y
tell (x:y:_) = "This list is long. The first two elements are: " ++ show x ++ " and " ++ show y

-- new length function
length' :: (Num b) => [a] -> b
length' [] = 0
length' (_:xs) = 1 + length' xs
