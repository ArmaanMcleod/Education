{-The function to the right doesn't compile because it uses a type synonym that has not been included!

  Figure out what the type synonym should be, and add it so the function will compile.
-}

-- put your type synonym definition here:
type Message = (String, Int)
-- or ([Char], Int)
-- or actually any numerical type instead of Int

valid :: Message -> Bool
valid (msg, mid) = correctLength && noSpaces && validID
    where
        correctLength = (length msg <= 140)
        noSpaces      = not (elem ' ' msg)
        validID       = mid >= 1000 && mid <= 9999