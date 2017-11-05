import Data.List
import Data.Char


-- Linked List data constructor
data List a = ListNode a (List a) | ListEnd
    deriving (Show, Eq, Ord)

data Tree a = Node a (Tree a) (Tree a) | Empty
    deriving (Show, Eq, Ord)

-- fibonacci
fib :: Int -> Int
fib 0 = 0
fib 1 = 1
fib n = fib(n-1) + fib(n-2)

fib' :: Int -> Int
fib' n
    | n < 0 = 0
    | n == 0 = 0
    | n == 1 = 1
    | otherwise = fib'(n-1) + fib'(n-2)

-- leap year checker
leap :: Int -> Bool
leap year
    | year `mod` 400 == 0 = True
    | year `mod` 100 == 0 = False
    | year `mod` 4 == 0 = True
    | otherwise = False

-- first n even numbers
evens :: Int -> [Int]
evens 0 = []
evens n = [x | x <- [2..n*2], even x]

evens' :: Int -> [Int]
evens' n = [2, 4 .. n*2]

-- linear search
-- can also just use elem function
-- elem :: (Eq a) => a -> [a] -> Bool
search :: (Eq a) => a -> [a] -> Bool
search _ [] = False
search y (x:xs)
    | y == x = True
    | otherwise = search y xs

-- maximum
-- Or could use maximum function
maximum' :: (Ord a) => [a] -> a
maximum' [] = error "Cant compute maximum of empty list"
maximum' [x] = x
maximum' (x:xs)
    | x > maxxs = x
    | otherwise = maxxs
    where 
        maxxs = maximum' xs

-- tail recursive maximum
maximum'' :: (Ord a) => [a] -> a
maximum'' [] = error "Cant compute maximum of empty list"
maximum'' [x] = x
maximum'' (x:xs) = go x xs
    where 
        go m [] = m 
        go m (y:ys)
            | m > y = go m ys
            | otherwise = go y ys

-- binary search
bsearch :: (Ord a) => a -> [a] -> Bool
bsearch _ [] = False
bsearch x ys
    | val > x = bsearch x (take(mid-1) ys)
    | val < x = bsearch x (drop(mid+1) ys)
    | otherwise = True
    where 
        mid = length ys `div` 2
        val = ys !! mid

-- all integer matches
evn :: Int -> Bool
evn x = x `mod` 2 == 0

big :: Int -> Bool
big x = x > 100

allsearch :: (Int -> Bool) -> [Int] -> [Int]
allsearch _ [] = []
allsearch f (x:xs)
    | f x = x : allsearch f xs
    | otherwise = allsearch f xs

-- Or using filter
-- filter :: (a -> Bool) -> [a] -> [a]
allsearch' :: (Int -> Bool) -> [Int] -> [Int]
allsearch' _ [] = []
allsearch' f xs = filter f xs

-- quicksort
qsort :: [Int] -> [Int]
qsort [] = []
qsort (pivot:others) = (qsort lowers) ++ [pivot] ++ (qsort highers)
    where
        lowers = filter (<pivot) others
        highers = filter (>=pivot) others

-- mergesort
msort :: [Int] -> [Int]
msort [] = []
msort [x] = [x]
msort xs = merge (msort first) (msort second)
    where
        first = take n xs
        second = drop n xs
        n = (length xs) `div` 2

merge :: [Int] -> [Int] -> [Int]
merge xs [] = xs
merge [] ys = ys
merge (x:xs) (y:ys)
    | x < y = x: merge xs (y:ys)
    | otherwise = y : merge (x:xs) ys

-- equality checker
setEq :: [Int] -> [Int] -> Bool
setEq xs ys = sort (nub xs) == sort (nub ys)

-- frequency 
freq :: [Int] -> [Int]
freq xs = map length (group (sort xs))

-- sum checking
checksum :: ([Int], Int) -> (Bool, Int)
checksum (lst, tot)
    | sum lst == tot = (True, sums)
    | otherwise = (False, sums)
    where sums = sum lst

-- my map function
map' :: (a -> b) -> [a] -> [b]
map' _ [] = []
map' f (x:xs) = f x : map f xs

-- middle element of a list
middle :: [a] -> a
middle xs = xs !! ((length xs) `div` 2)

-- maximum element in a linked list
-- data List a = ListNode a (List a) | ListEnd
mymaximum :: (Ord a) => List a -> a
mymaximum (ListNode x ListEnd) = x
mymaximum (ListNode x xs)
    | x > maxxs = x
    | otherwise = maxxs
    where maxxs = mymaximum xs

-- binary tree height
-- data Tree a = Node a (Tree a) (Tree a) | Empty
size :: Tree a -> Int
size Empty = 0
size (Node _ l r) = 1 + size l + size r

height :: Tree a -> Int
height Empty = 0
height (Node _ l r) = 1 + max (height l) (height r)

-- search binary tree
searchBST :: (Ord a) => a -> Tree a -> Bool
searchBST _ Empty = False
searchBST y (Node x l r)
    | y > x = searchBST y r
    | y < x = searchBST y l
    | otherwise = True

-- insertion binary tree
insertBST :: (Ord a) => a -> Tree a -> Tree a
insertBST y Empty = Node y Empty Empty
insertBST y (Node x l r)
    | y > x =  Node x l (insertBST y r)
    | y < x = Node x (insertBST y l) r
    | otherwise = Node x l r

-- filter
filter' :: (a -> Bool) -> [a] -> [a]
filter' _ [] = []
filter' f (x:xs)
    | f x = x : filter' f xs
    | otherwise = filter' f xs

-- finds the number of matching elements between both lists
matches :: Eq a => [a] -> [a] -> Int
matches xs ys = length [(x, y) | x <- xs, y <- ys, x == y]

-- DNA checking
compDNA :: String -> String -> Bool
compDNA xs ys = and [compBase x y | (x, y) <- zip xs ys]

compBase :: Char -> Char -> Bool
compBase 'A' 'T' = True
compBase 'T' 'A' = True
compBase 'C' 'G' = True
compBase 'G' 'C' = True
compBase  _   _  = False

keepl :: Int -> [a] -> [a]
keepl _ [] = []
keepl k xs = [last x | x <- splitlists k xs, length x == k]

splitlists :: Int -> [a] -> [[a]]
splitlists _ [] = []
splitlists k xs = first : (splitlists k rest)
    where
        (first, rest) = splitAt k xs

filter_map :: (a -> Bool) -> (a -> b) -> [a] -> [b]
filter_map _ _ [] = []
filter_map f1 f2 (x:xs) = 
    let newxs = filter_map f1 f2 xs
    in if f1 x then f2 x : newxs else newxs

getList :: Integer -> [Integer]
getList n = [toInteger (digitToInt x) | x <- show n]

groupList :: [Integer] -> [(Integer, Int)]
groupList xs = nub [(x,c) | x <- xs, let c = (length . filter (==x)) xs, c > 0]

getSequence :: [(Integer, Int)] -> [Integer]
getSequence (x:xs) = snd x : fst x : getSequence xs

getLists :: Integer -> [Integer]
getLists 0 = []
getLists 1 = [1]
getLists n = 