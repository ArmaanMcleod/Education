{-Using your newfound knowledge of operators, write a Haskell function leap which takes an integer year year and returns True if year is a leap year, or False otherwise.

  A year is a leap year if it is divisible by 4, unless it is also divisible by 100 but not by 400.

  For example:

  Main> leap 2000
  True
  Main> leap 2003
  False
  Main> leap 2004
  True
  Main> leap 1900
  False
-}

-- first solution
leap1 :: Int -> Bool
leap1 year = (year `mod` 4 == 0) && (year `mod` 400 == 0 || year `mod` 100 /= 0)

-- second solution
leap2 :: Int -> Bool
leap2 year
    | year `mod` 4   /= 0 = False
    | year `mod` 100 /= 0 = True
    | year `mod` 400 /= 0 = False
    | otherwise           = True





