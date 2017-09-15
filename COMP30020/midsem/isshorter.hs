is_shorter :: Int -> String -> Bool
is_shorter n s = n > length s

filter' :: (a -> Bool) -> [a] -> [a]
filter' _ [] = []
filter' f (x:xs)
    | f x = x : filter' f xs
    | otherwise = filter' f xs

isPalindrome :: (Integral a) => a -> Bool

