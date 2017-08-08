{-
  Write a recursive Haskell function fib, which takes an integer input n and returns the nth Fibonacci number.
-}

fib :: Int -> Int
fib 0 = 0
fib 1 = 1
fib n = fib (n-1) + fib (n-2)