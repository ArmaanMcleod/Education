data Tree a = Node a (Tree a) (Tree a) | Empty

height :: Tree a -> Int
height Empty        = 0
height (Node x l r) = 1 + (max (height l) (height r))