search :: Int -> [Int] -> Bool
search x [] = False
search x (y:ys)
    | x == y    = True
    | otherwise = search x ys