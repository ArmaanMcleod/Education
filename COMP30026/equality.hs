import Data.List

-- disinct matching
distinctElem :: [Int] -> [Int]
distinctElem [] = []
distinctElem xs = sort (nub xs)

setEq :: [Int] -> [Int] -> Bool
setEq xs ys
    | distinctElem xs == distinctElem ys = True
    | otherwise = False








