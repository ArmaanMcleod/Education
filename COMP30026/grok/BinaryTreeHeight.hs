{-Now it's your turn to write a tree function!

  Write a recursive function height which takes a binary tree and calculates its height: 
  the number of nodes in the longest path from root to leaf.

  For example:

  Main> height (Node "stump" Empty Empty)
  1
  Main> height (Node "trunk" Empty (Node "branch" (Node "leaf" Empty Empty) Empty))
  3

  data Tree a = Node a (Tree a) (Tree a) | Empty
-}

height :: Tree a -> Int
height Empty        = 0
height (Node x l r) = 1 + (max (height l) (height r))