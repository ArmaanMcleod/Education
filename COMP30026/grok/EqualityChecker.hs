import Data.List

setEq :: [Int] -> [Int] -> Bool
setEq xs ys = sort (nub xs) == sort (nub ys)