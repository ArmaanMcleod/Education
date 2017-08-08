{-Now we have a home-made replacement for Haskell's built-in list type!

  Here's an implementation of a list length function made specially for our custom type:

  data List a = ListNode a (List a) | ListEnd
​
  mylength :: List a -> Int
  mylength ListEnd         = 0
  mylength (ListNode x xs) = 1 + mylength xs
  Based on this example and what we have learned about types up to this point, 
  implement a custom maximum function. 
  It should be called mymaximum and work with non-empty lists of our custom List type.

  For example:

  Main> mymaximum (ListNode 10 ListEnd)
  10
  Main> mymaximum (ListNode 20 (ListNode 10 ListEnd))
  20
-}

data List a = ListNode a (List a) | ListEnd

mymaximum :: Ord a => List a -> a
mymaximum (ListNode x ListEnd) = x
mymaximum (ListNode x xs)
    | x > maxxs = x
    | otherwise = maxxs
    where maxxs = mymaximum xs