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