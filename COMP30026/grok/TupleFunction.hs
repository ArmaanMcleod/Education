{-Write a function checksum that takes a ([Int], Int) tuple (lst,tot) and checks whether 
  the sum of the elements in lst is equal to tot. It should return a tuple (True, tot) 
  if the sum is correct, or (False, x) if otherwise, with x as the correct sum.

  For example,


  checksum ([1,2,3],6)
  (True,6)
  checksum ([1,2,3,4],9)
  (False,10)
  
  All you should have to do here is figure out how to structure the function. 
  Can you guess how to pattern match against a tuple of two elements?
-}

-- solution 1
checksum1 :: ([Int], Int) -> (Bool, Int)
checksum1 (lst, tot)
    | tot == truetot = (True, truetot)
    | otherwise      = (False, truetot)
    where truetot = sum lst

-- solution 2
checksum2 :: ([Int], Int) -> (Bool, Int)
checksum2 (lst, tot) = (truetot == tot, truetot) where truetot = sum lst