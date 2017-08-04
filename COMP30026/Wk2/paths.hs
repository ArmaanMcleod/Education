-- finds all paths from bottom left corner to top right corner in a n x m grids

paths :: Integer -> Integer -> Integer
paths n m 
    | n == 1 && m == 1 = 1
    | n == 1 = paths n (m-1) 
    | m == 1 = paths (n-1) m
    | otherwise = paths (n-1) m + paths m (n-1)