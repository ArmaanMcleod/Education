import Data.List

-- groups and counts frequencies
groupAll :: [Int] -> [[Int]]
groupAll xs = group (sort xs)

frequency :: [Int] -> [Int] 
frequency list = map length (groupAll list)