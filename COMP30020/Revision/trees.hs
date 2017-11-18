data Tree a = Empty | Node (Tree a) a (Tree a)
    deriving (Show, Eq, Ord)

buildtree :: [a] -> Tree a
buildtree [] = Empty
buildtree xs = Node (buildtree as) midval (buildtree (tail bs))
     where
        halflength = length xs `div` 2
        midval     = xs !! halflength
        (as,bs)    = splitAt halflength xs

contents_tree :: Tree a -> [a]
contents_tree Empty = []
contents_tree (Node l a r) = contents_tree(l) ++ [a] ++ contents_tree(r)

buildbst :: (Ord a) => [a] -> Tree a
buildbst [] = Empty
buildbst (x:xs) = insert_tree x (buildbst xs)

tree_sort :: (Ord a) => [a] -> [a]
tree_sort xs = contents_tree (buildbst xs)

insert_tree :: (Ord a) => a -> Tree a -> Tree a
insert_tree x Empty = Node Empty x Empty
insert_tree x (Node l y r)
    | y == x = Node l y r
    | y < x = Node l y (insert_tree x r)
    | y > x = Node (insert_tree x l) y r

size_tree :: Tree a -> Int
size_tree Empty = 0
size_tree (Node l _ r) = 1 + size_tree l + size_tree r

height_tree :: Tree a -> Int
height_tree Empty = 0
height_tree (Node l _ r) = 1 + max (height_tree l) (height_tree r)

search_tree :: (Ord a) => a -> Tree a -> Bool
search_tree _ Empty = False
search_tree y (Node l x r)
    | y > x = search_tree y r
    | y < x = search_tree y l
    | otherwise = True

map_tree :: (a -> a) -> Tree a -> Tree a
map_tree _ Empty = Empty
map_tree f (Node l x r) = Node (map_tree f l) (f x) (map_tree f r)

foldr_tree :: (a -> b -> a -> a) -> a -> Tree b -> a
foldr_tree _ b Empty = b
foldr_tree f b (Node l x r) = f (foldr_tree f b l) x (foldr_tree f b r)



