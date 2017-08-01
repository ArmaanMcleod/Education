data Tree a = Node a (Tree a) (Tree a) | Empty
    deriving Show

-- size of binary tree
size :: Tree a -> Int
size Empty = 0
size (Node x l r) = 1 + size l + size r

-- depth of binary tree
height :: Tree a -> Int
height Empty = 0
height (Node x l r) = 1 + max (height l) (height r)

-- searching a binary tree
search :: Ord a => a -> Tree a -> Bool
search x Empty = False
search x (Node y l r)
    | x == y = True
    | x < y  = search x l
    | x > y  = search x r

-- insertion of binary tree
insert :: (Ord a) => a -> Tree a -> Tree a
insert x Empty = Node x Empty Empty
insert x (Node y l r)
    | y == x = Node y l r
    | y < x = Node y l (insert x r)
    | y > x = Node y (insert x l) r






