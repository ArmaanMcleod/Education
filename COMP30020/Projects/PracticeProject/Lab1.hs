-- COMP30020/COMP90048 Optional Assignment

module Lab1 (subst, interleave, unroll) where

-- Question 1
subst :: Eq t => t -> t -> [t] -> [t]
subst a b xs = [if x == a then b else x | x <- xs]

-- Question 2
interleave :: [t] -> [t] -> [t]
interleave xs [] = xs
interleave [] ys = ys
interleave (x:xs) (y:ys) = x : y : interleave xs ys

-- Question 3
unroll :: Int -> [a] -> [a]
unroll x ys = take x (cycle ys)





