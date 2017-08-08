{-Over to you!

  Write a function insert which takes an element and a binary search tree as inputs and 
  inserts the element into the binary search tree, returning the resulting modified tree. 
  If the element already exists in the search tree, the tree should not be changed.

  For example:

  Main> insert 3 Empty
  Node 3 Empty Empty
  Main> insert 4 (Node 3 Empty (Node 5 Empty Empty))
  Node 3 Empty (Node 5 (Node 4 Empty Empty) Empty)
  Be sure to think about the appropriate type signature for your function!
-}

data Tree a = Node a (Tree a) (Tree a) | Empty
    deriving Show

insert :: Ord a => a -> Tree a -> Tree a
insert x Empty = Node x Empty Empty
insert x (Node y l r)
    | x == y = Node y l r
    | x < y  = Node y (insert x l) r
    | x > y  = Node y l (insert x r)