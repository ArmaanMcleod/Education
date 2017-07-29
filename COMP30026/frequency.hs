import Data.List

distinctElem :: [Int] -> [Int]
distinctElem [] = []
distinctElem xs = sort (nub xs)

groupAll :: [Int] -> [[Int]]
groupAll xs = group (sort xs)

frequency :: [Int] -> [Int] 
frequency list = map (\l -> length l) (groupAll list)