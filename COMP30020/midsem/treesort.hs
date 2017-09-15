data Tree a = Empty | Node a (Tree a) (Tree a )
    deriving (Eq, Show, Ord)

insertTree :: (Ord a) => a -> Tree a -> Tree a
insertTree x Empty = Node x Empty Empty
insertTree x (Node y l r)
    | x > y = Node y l (insertTree x r)
    | x < y = Node y (insertTree x l) r
    | otherwise = Node x l r

searchTree :: (Ord a) => a -> Tree a -> Bool
searchTree x Empty = False
searchTree x (Node y l r)
    | x == y = True
    | x > y = searchTree x r
    | otherwise = searchTree x l 

buildTree :: (Ord a) => [a] -> Tree a
buildTree [] = Empty
buildTree (x:xs) = insertTree x (buildTree xs)

contentsTree :: Tree a -> [a]
contentsTree Empty = []
contentsTree (Node x l r) = contentsTree l ++ [x] ++ contentsTree r

sortTree :: (Ord a) => [a] -> [a]
sortTree [] = []
sortTree xs = contentsTree (buildTree xs)

