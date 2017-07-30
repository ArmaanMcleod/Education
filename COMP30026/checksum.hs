-- checks sum of tuples
checksum :: ([Int], Int) -> (Bool, Int)
checksum lst tot
    | sums == tot = (True, sums)
    | otherwise = (False, sums)
    where sums = sum lst