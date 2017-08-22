import Data.List

-- Binary search tree type declaration
data Tree k v = Leaf | Node k v (Tree k v) (Tree k v)
    deriving (Eq, Show)

-- eval expression
data Expression 
    = Var Variable
    | Num Integer
    | Plus Expression Expression
    | Minus Expression Expression
    | Times Expression Expression
    | Div Expression Expression

data Variable = A | B

-- Question 2
ftoc :: Double -> Double
ftoc f = ((5 * 1.0) / 9) * (f - 32)

-- Question 3
quadRoots :: Double -> Double -> Double -> [Double]
quadRoots a b c
    | det > 0 = [left + right, left - right]
    | det == 0 = [left]
    | otherwise = []
    where 
      det   = b * b - 4 * a * b
      left  = -b / denom
      right = sqrt(det/denom)
      denom = 2 * a

isSorted :: (Ord a) => [a] -> Bool
isSorted [_] = True
isSorted (x:xs)
    | x <= head xs = isSorted xs
    | otherwise = False

-- Question 4
--  Merging two sorted lists
merge :: (Ord a) => [a] -> [a] -> [a]
merge [] [] = []
merge [] xs = xs
merge ys [] = ys
merge (x:xs) (y:ys)
    | x <= y = x : merge xs  (y:ys)
    | otherwise = y : merge (x:xs) ys

-- Question 5
qsort :: (Ord a) => [a] -> [a]
qsort [] = []
qsort (pivot:others) = qsort(lowers) ++ [pivot] ++ qsort(highers)
    where lowers = filter (<pivot) others
          highers = filter (>=pivot) others

-- Question 6
--data Tree k v = Leaf | Node k v (Tree k v) (Tree k v)
  --deriving (Eq, Show)

same_shape :: Tree a b -> Tree c d -> Bool
same_shape Leaf Leaf = True
same_shape (Node _ _ l1 r1) (Node _ _ l2 r2) = same_shape l1 l2 && same_shape r1 r2
same_shape _ _ = False






