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





