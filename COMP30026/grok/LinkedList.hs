data List a = ListNode a (List a) | ListEnd

mymaximum :: Ord a => List a -> a
mymaximum (ListNode x ListEnd) = x
mymaximum (ListNode x xs)
    | x > maxxs = x
    | otherwise = maxxs
    where maxxs = mymaximum xs