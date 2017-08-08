{-Write a recursive Haskell function fib, which takes an integer input n and returns the nth Fibonacci number.
  Define your function using one pattern and multiple guards.
-}

fib :: Int -> Int
fib n
    | n <= 0    = 0
    | n == 1    = 1
    | otherwise = fib (n-1) + fib (n-2)