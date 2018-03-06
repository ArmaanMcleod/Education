import Data.List

data Set a = Set [a]

union' :: Set a -> Set a -> Set a
union' xs [] = xs
union' [] ys = ys
union' (x:xs)