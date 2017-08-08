{-Write a polymorphic function middle that takes a non-empty list (of any type) and returns the middle element of the list.

  In the case an even-length list, where there isn't a unique middle element, you should return the second of the two elements closest to the middle.

  For example:


  Main> middle [4,3,5]
  3
  Main> middle [10,2,5,1]
  5
  Main> middle "superstar"
  'r'
-}

middle :: [a] -> a
middle xs = xs !! (length xs `div` 2)