data Tree a = Node a (Tree a) (Tree a) | Empty
    deriving Show

tree :: Tree Int
tree = Node 3 (Node 9 (Node 10 Empty Empty) (Node 5 Empty Empty) (Node 7 Empty Empty)