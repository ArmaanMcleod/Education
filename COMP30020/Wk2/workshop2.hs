-- Question 3
factorial :: Integer -> Integer
factorial 0 = 1
factorial n = n * factorial(n-1)

factorial' :: Integer -> Integer
factorial' n = product [1..n]

-- Question 4
-- search functions
linearsearch :: (Ord a) => a -> [a] -> Bool
linearsearch _ [] = False
linearsearch x (y:ys)
    | x == y = True
    | otherwise = linearsearch x ys

binarysearch :: (Ord a) => a -> [a] -> Bool
binarysearch _ [] = False
binarysearch x (y:ys)
    | val > x = binarysearch x (take(mid-1) ys)
    | val < x = binarysearch x (drop(mid+1) ys)
    | otherwise = True
    where mid = (length ys) `div` 2
          val = ys!!mid


myElem :: (Ord a) => a -> [a] -> Bool
myElem x ys = binarysearch x ys

-- Question 5
longestPrefix :: (Eq a) => [a] -> [a] -> [a]
longestPrefix _ [] = []
longestPrefix [] _ = []
longestPrefix (x:xs) (y:ys)
    | x == y = x : longestPrefix xs ys 
    | otherwise = []

-- Question 7
minmax :: Int -> Int -> [Int]
minmax min max = [min..max]
    

-- Question 2
-- type constructor = data Card
-- data constructor = Card Suit Rank
data Card = Card Suit Rank | Joker
    deriving (Eq, Show)

data Suit = Hearts | Diamonds | Spades | Clubs
    deriving (Eq, Show)

data Rank = Ace | Two | Three | Four | Five | Six | Seven |
            Eight | Nine | Jack | Queen | King
    deriving (Eq, Show)


-- Question 3 Html font tags
-- Record constructors {}
data HTMLFontTag = HTMLFontTag {fontFace :: Maybe String
                                , fontSize :: Maybe Int
                                , fontColour :: Maybe Colour}

data Colour = CRGB Int Int Int | CHEX Int | CNAME String






