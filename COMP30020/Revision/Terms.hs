data Var = VarName String
    deriving (Eq, Ord, Read, Show)

data FSym = FSym String
    deriving (Eq, Ord, Read, Show)

data Term
    = TermVar Var
    | TermNum Int
    | TermFSym FSym [Term]
    deriving (Eq, Ord, Read, Show)


print_term :: Term -> IO ()
print_term term = print_term_helper 0 term

print_spaces :: Int -> String
print_spaces n = take (n * 4) (cycle " ")

print_term_helper :: Int -> Term -> IO ()
print_term_helper n (TermVar (VarName str)) = putStrLn (print_spaces n ++ str)
print_term_helper n (TermNum x) = print (print_spaces n ++ show x)
print_term_helper n (TermFSym (FSym str) xs) = do
        putStrLn (print_spaces n ++ str)
        print_list (n+1) xs

print_list :: Int -> [Term] -> IO ()
print_list _ [] = return ()
print_list n (x:xs) = do
    print_term_helper n x
    print_list n xs