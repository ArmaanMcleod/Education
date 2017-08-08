{-Now it's your turn:

  Define a function tree which takes no arguments and returns the following Tree of integers:


         (3)
        /   \
      (9)   (7)
      /  \
    (10) (5)
-}

data Tree a = Node a (Tree a) (Tree a) | Empty
    deriving Show

tree :: Tree Int
tree = Node 3 (Node 9 (Node 10 Empty Empty) (Node 5 Empty Empty) (Node 7 Empty Empty)