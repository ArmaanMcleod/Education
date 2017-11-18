data Tree a = Node a (Tree a) (Tree a) | Empty
    deriving (Show, Eq, Ord)

treeList :: Tree a -> [a]
treeList Empty = []
treeList (Node x l r) = treeList l ++ [x] ++ treeList r