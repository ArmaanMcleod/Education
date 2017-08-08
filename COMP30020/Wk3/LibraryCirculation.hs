data PubFreq = Days Int | Months Int
data LibItem = Book Int String String | PubFreq Int String PubFreq

title :: LibItem -> String
title (Book _ title _) = title
title (Periodical _ title _) = title

-- Representing expressions in haskell
data Expr 
    = Number Int -- first is a data constructor, rest is a type
    | Variable String
    | Binop Binop Expr Expr
    | Unop Unop Expr

data Binop = Plus | Minus | Times | Divide
data Unop = Negate
