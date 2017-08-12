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


