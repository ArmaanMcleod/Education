data Tree a = Empty | Node (Tree a) a (Tree a)
    deriving (Show, Eq, Ord)

buildtree :: [a] -> Tree a
buildtree [] = Empty
buildtree xs = Node midval (buildtree as) (buildtree (tail bs))
     where
        halflength = length xs `div` 2
        midval     = xs !! halflength
        (as,bs)    = splitAt halflength xs

contents_tree :: Tree a -> [a]
contents_tree Void = []
contents_tree (Node a l r) = contents_tree(l) ++ [a] ++ contents_tree(r)

buildbst :: (Ord a) => [a] -> BinTree a
buildbst [] = Void
buildbst (x:xs) = insertbst x (buildbst xs)

tree_sort :: (Ord a) => [a] -> [a]
tree_sort xs = contents_tree (buildbst xs)

insert_tree :: (Ord a) => a -> Tree a -> Tree a
insert_tree x Void = Node x Void Void
insert_tree x (Node y l r)
    | y == x = Node y l r
    | y < x = Node y l (insert_tree x r)
    | y > x = Node y (insert_tree x l) r

size_tree :: Tree a -> Int
size_tree Empty = 0
size_tree (Node _ l r) = 1 + size_tree l + size_tree r

height_tree :: Tree a -> Int
height_tree Empty = 0
height_tree (Node _ l r) = 1 + max (height_tree l) (height_tree r)

search_tree :: (Ord a) => a -> Tree a -> Bool
search_tree _ Empty = False
search_tree y (Node x l r)
    | y > x = search_tree y r
    | y < x = search_tree y l
    | otherwise = True

map_tree :: (a -> a) -> Tree a -> Tree a
map_tree _ Empty = Empty
map_tree f (Node l x r) = Node (map_tree f l) (f x) (map_tree f r)
