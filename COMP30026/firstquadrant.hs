data Point = Pt Float Float

goodPoint :: Point -> Bool
goodPoint (Pt x y)
    | x > 0 && y > 0 = True
    | otherwise = False

--mymaximum :: List a -> Int
--mymaximum (ListNode x xs)
    --| x > maxTail = x 
    --| otherwise = maxTail
    --where maxTail = mymaximum xs
