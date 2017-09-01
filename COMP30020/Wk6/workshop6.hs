-- Question 1
maybeApply :: (a -> b) -> Maybe a -> Maybe b
maybeApply f Nothing = Nothing
maybeApply f (Just x) = Just (f x)

-- Question 2
zWith :: (a -> b -> c) -> [a] -> [b] -> [c]
zWith f (x:xs) (y:ys) = f x y : zWith f xs ys
zWith _ _ _ = []

minus :: Int -> Int -> Int
minus x y = x - y

-- Question 3
linearEq :: (Num t) => t -> t -> [t] -> [t]
linearEq a b xs = map f xs
    where
        f x = a * x + b

linearEq' :: (Num t) => t -> t -> [t] -> [t]
linearEq' a b xs = map (\x -> a*x + b) xs

-- Question 4
sqrtPM :: (Floating a, Ord a) => a -> [a]
sqrtPM x
    | x > 0 = let y = sqrt x in [y, -y]
    | x == 0 = [0]
    | otherwise = []

allSqrts :: (Floating a, Ord a) => [a] -> [a]
allSqrts [] = []
allSqrts (x:xs) = sqrtPM x ++ allSqrts xs

allSqrts' :: (Floating a, Ord a) => [a] -> [a]
allSqrts' xs = flatten $ map sqrtPM xs

flatten :: [[a]] -> [a]
flatten [] = []
flatten (x:xs) = x ++ flatten xs

-- Question 5
sqrtNonNeg :: (Ord a, Floating a) => [a] -> [a]
sqrtNonNeg xs = map sqrt $ filter (>= 0) xs
