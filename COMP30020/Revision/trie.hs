data Tree a = Null | Node a (Tree a) (Tree a)
     deriving (Read,Show)

-- addNode n t adds node n to binary search tree t
addNode :: Ord a => a -> Tree a -> Tree a
addNode m Null = Node m Null Null
addNode m (Node n t1 t2)
   | m<n       = Node n (addNode m t1) t2
   | otherwise = Node n t1 (addNode m t2)

-- makeTree ns makes a binary search tree from the list of nodes ns
makeTree :: Ord a => [a] -> Tree a
makeTree []     = Null
makeTree (x:xs) = addNode x (makeTree xs)

-- inOrder t returns the list of nodes in an inorder traversal of tree t
inOrder :: Tree a -> [a]
inOrder Null           = []
inOrder (Node n t1 t2) = (inOrder t1) ++ [n] ++ (inOrder t2)

sortTree :: (Ord a) => [a] -> [a]
sortTree xs = inOrder (makeTree xs)

maxTree :: (Ord a) => [a] -> a
maxTree = head . reverse . sortTree

sumTuples list = (sum [x | (x, _) <- list], sum [y | (_, y) <- list])