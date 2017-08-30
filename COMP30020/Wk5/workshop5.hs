triple :: (Num a) => [a] -> (Int, a, a)
triple xs = (len, sums, sumsSquare)
    where len = length xs
          sums = sum xs
          sumsSquare = sum (map (^2) xs)

triple' :: (Num a) => [a] -> (Int, a, a)
triple' xs = go xs (0,0,0)
    where go [] acc = acc
          go (x:xs) (c, s, sq) = go xs (c+1, s+x, sq + x^2)
