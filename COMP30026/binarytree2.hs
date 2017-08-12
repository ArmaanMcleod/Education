data BinTree a = Void | Node a (BinTree a) (BinTree a)
   deriving (Eq, Show)

buildtree :: [a] -> BinTree a
buildtree []
   = Void
buildtree xs
   = Node midval (buildtree as) (buildtree (tail bs))
     where
        halflength = length xs `div` 2
        midval     = xs !! halflength
        (as,bs)    = splitAt halflength xs

contents :: BinTree a -> [a]
contents Void = []
contents (Node a l r) = contents(l) ++ [a] ++ contents(r)

insertbst :: (Ord a) => a -> BinTree a -> BinTree a
insertbst x Void = Node x Void Void
insertbst x (Node y l r)
    | y == x = Node y l r
    | y < x = Node y l (insertbst x r)
    | y > x = Node y (insertbst x l) r

buildbst :: (Ord a) => [a] -> BinTree a
buildbst [] = Void
buildbst (x:xs) = insertbst x (buildbst xs)

buildbst' :: (Ord a) => [a] -> BinTree a
buildbst' xs = foldl (\acc x -> insertbst x acc) Void (reverse xs)






    



    
    


