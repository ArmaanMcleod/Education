{-In the editor you will see the implementation of quicksort from the Grok module on lists. Back then, we were defining everything as functions dealing exclusively with single types.

  Change the definition of qsort so that it can sort a list of anything in the Ord type class.

  For example:


  Main> qsort [1,5,4,6,3,2]
  [1,2,3,4,5,6]
  Main> qsort "banana"
  "aaabnn"
  Main> qsort [3.5, 5.0, 0.0, 6.1]
  [0.0,3.5,5.0,6.1]
-}

qsort :: Ord a => [a] -> [a]
qsort [] = []
qsort (pivot:others) = (qsort lowers) ++ [pivot] ++ (qsort highers)
    where lowers  = filter (<pivot)  others
          highers = filter (>=pivot) others