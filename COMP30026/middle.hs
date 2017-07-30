-- finds middle of haskell list

middle :: [a] -> a
middle xs = xs !! ((length xs) `div` 2)