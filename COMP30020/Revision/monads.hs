
hello1 :: IO()
hello1 =
    putStr "Hello, "
    >>=
    \_ -> putStrLn "world!"

greet1 :: IO()
greet1 = 
    putStr "Greetings! What is your name? "
    >>=
    \_ -> getLine
    >>=
    \name -> (
        putStr "Where are you from? "
        >>=
        \_ -> getLine
        >>=
        \town ->
        let msg = "Welcome, " ++ name ++
                  " from " ++ town
        in putStrLn msg
    )

-- Using do blocks
hello2 :: IO()
hello2 = do
    putStr "Hello, "
    putStrLn "world"

greet2 :: IO ()
greet2 = do
    putStr "Greetings! What is your name? "
    name <- getLine
    putStr "Where are you from? "
    town <- getLine
    let msg = "Welcome, " ++ name ++ " from " ++ town
    putStrLn msg
