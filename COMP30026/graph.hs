type Graph = (Int, [(Int, Int)])

wfg :: Graph -> Bool
wfg (_, []) = True
wfg (n, (a,b):xs)
    | cmp = False
    | otherwise = wfg (n, xs)
    where cmp = a > n || b > n || a < 0 || b < 0


