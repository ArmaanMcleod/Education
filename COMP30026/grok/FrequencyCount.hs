import Data.List

freqs :: [Int] -> [Int]
freqs xs = map length (group (sort xs))