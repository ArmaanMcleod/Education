type Graph = (Int, [(Int, Int)])

type Colouring = [Colour]

data Colour =  Blue | Green | Red
    deriving (Eq, Show)

wfg :: Graph -> Bool
wfg (_, []) = True
wfg (n, (a,b):xs)
    | cmp = False
    | otherwise = wfg (n, xs)
    where cmp = a > n || b > n || a < 0 || b < 0

well_coloured :: Graph -> Colouring -> Bool
well_coloured (_, []) _ = True
well_coloured (n, (a,b):xs) cs
    | cmp = False
    | otherwise = well_coloured (n, xs) cs
    where cmp = cs !! a == cs !! b









