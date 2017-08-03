-- solution 1
checksum1 :: ([Int], Int) -> (Bool, Int)
checksum1 (lst, tot)
    | tot == truetot = (True, truetot)
    | otherwise      = (False, truetot)
    where truetot = sum lst

-- solution 2
checksum2 :: ([Int], Int) -> (Bool, Int)
checksum2 (lst, tot) = (truetot == tot, truetot) where truetot = sum lst