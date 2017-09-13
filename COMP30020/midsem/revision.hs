import Data.List

data List a = ListNode a (List a) | ListEnd

data Tree k v = Node k v (Tree k v) (Tree k v) | Leaf

data BST a = Empty | Item (BST a) a (BST a)

min' :: (Ord a) => a -> a -> a
min' a b
    | a >= b = b
    | otherwise = a

maximum' :: (Ord a ) => [a] -> a
maximum' [] = error "Empty List"
maximum' [x] = x
maximum' (x:xs)
    | x > maxTail = x
    | otherwise = maxTail
    where maxTail = maximum' xs

fst' :: (a, b) -> a
fst' (x, y) = x

head' :: [a] -> a
head' (x:_) = x

take' :: Int -> [a] -> [a]
take' 0 _ = []
take' 1 xs = [head xs]
take' n (x:xs) = x : take' (n-1) xs

sum' :: (Num a) => [a] -> a
sum' [] = 0
sum' [x] = x
sum' (x:xs) = x + sum' xs

elem' :: (Eq a ) => a -> [a] -> Bool
elem' _ [] = False
elem' n (x:xs)
    | x == n = True
    | otherwise = elem' n xs

length' :: [a] -> Int
length' [] = 0
length' (_:xs) = 1 + length' xs

reverse' :: [a] -> [a]
reverse' [] = []
reverse' [x] = [x]
reverse' (x:xs) = reverse xs ++ [x]

map' :: (a -> b) -> [a] -> [b]
map' _ [] = []
map' f (x:xs) = f x : map' f xs

zip' :: [a] -> [b] -> [(a,b)]
zip' [] _ = []
zip' _ [] = []
zip' (x:xs) (y:ys) = (x, y) : zip' xs ys 

filter' :: (a -> Bool) -> [a] -> [a]
filter' _ [] = []
filter' f (x:xs)
    | f x = x : filter' f xs
    | otherwise = filter' f xs

minimumList :: (Ord a) => List a -> a
minimumList (ListNode x ListEnd) = x
minimumList (ListNode x xs) 
   | x < mins = x
   | otherwise = mins
   where mins = minimumList xs 

insertBST :: (Ord a) => a -> BST a -> BST a
insertBST x Empty = Item Empty x Empty
insertBST x (Item l y r)
    | x < y = Item (insertBST x l) y r
    | x > y = Item l y (insertBST x r)
    | otherwise = (Item l x r)
