data Tree a = Empty | Node (Tree a) a (Tree a)
    deriving (Show, Eq, Ord)

maybe_tail :: [a] -> Maybe [a] 
maybe_tail [] = Nothing
maybe_tail (_:xs) = Just xs

maybe_drop :: Int -> [a] -> Maybe [a]
maybe_drop 0 xs = Just xs
maybe_drop n xs | n > 0 = 
    let mt = maybe_tail xs in 
    case mt of
            Nothing -> Nothing
            Just xs1 -> maybe_drop (n-1) xs1

maybe_drop' :: Int -> [a] -> Maybe [a]
maybe_drop' 0 xs = Just xs
maybe_drop' n xs | n > 0 = 
    maybe_tail xs >>= maybe_drop' (n-1) 

print_tree :: (Show a) => Tree a -> IO ()
print_tree Empty = return()
print_tree (Node l x r) = do
    print_tree l
    print x
    print_tree r

is_string_digits :: String -> Bool
is_string_digits [] = False
is_string_digits xs = (length (filter isDigit xs) == length xs)

str_to_int_list :: String -> [Int]
str_to_int_list [] = []
str_to_int_list xs
    | is_string_digits xs = [digitToInt(x) | x <- xs]
    | otherwise = []

str_to_num :: String -> Maybe Int
str_to_num xs
    | intlist /= [] = Just (go intlist 0)
    | otherwise = Nothing
    where intlist = str_to_int_list xs
          go [] acc = acc
          go (x:xs) acc = go xs ((acc * 10) + x)

sum_numbers :: IO Int
sum_numbers = do
    line <- getLine
    let num = str_to_num line
    case num of
        Nothing -> return 0
        Just num -> do
            sum <- sum_numbers
            return (num + sum)

sum_numbers' :: IO Int
sum_numbers' = 
    getLine >>= 
        \line -> case str_to_num line of
            Nothing -> return 0
            Just num ->
                sum_numbers' >>=
                    \sum -> return (num + sum)

sum_list_numbers :: IO Int
sum_list_numbers = do
    sums <- list_numbers
    return (sum sums)

list_numbers :: IO [Int]
list_numbers = do
    line <- getLine
    let num = str_to_num line
    case num of
        Nothing = return []
        Just num -> do
            sum <- list_numbers
            return (num:sum)