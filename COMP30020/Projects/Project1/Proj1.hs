--  File           : proj1.hs
--  Author         : Armaan Dhaliwal-McLeod
--  Student Number : 837674
--  Subject        : COMP30020 Declarative Programming

-- Module declaration
module Proj1 (initialGuess, nextGuess, GameState) where 

-- Libraries used in this module
import Data.List 
import Data.Ord

-- Game State type
-- Used for storing previous targets
type GameState = [[String]]

-- Score type
type Score = (Int, Int, Int)

-- data type for components of a Musical note
data MusicalType = Pitch | Note | Octave
    deriving (Eq, Show, Ord)

-- Produces all possible pitch combinations 
-- Takes in two lists of strings
-- Returns a list of strings
allCombinations :: [String] -> [String] -> [String]
allCombinations xs ys = [x ++ y | x <- xs, y <- ys]

-- Credit https://wiki.haskell.org/99_questions/Solutions/26
-- Idea taken from above site, code written by me
-- Produces all possible combinations of pitches
-- Takes in a integer, and list of strings
-- Returns a game state type
pitchCombinations :: Int -> [String] -> GameState
pitchCombinations _ [] = [[]]
pitchCombinations 0 _ = [[]]
pitchCombinations n (x:xs) = start ++ others
    where start = [x : rest | rest <- pitchCombinations(n-1) xs]
          others
              | n <= length xs = pitchCombinations n xs
              | otherwise = []

-- Similar to 'pitchCombinations'
-- This function is more convenient to call
-- Takes in no arguements
-- Returns a game state
chordCombinations :: GameState
chordCombinations = pitchCombinations 3 $ allCombinations notes octaves
    where
        notes = [[x] | x <- ['A'..'G']]
        octaves = [show y | y <- [1..3]]

-- Hardcoded first guess
-- This was found through thorough testing
-- Takes in no arguements
-- Returns a hardcoded list of strings
firstGuess :: [String]
firstGuess = ["A1", "B1", "C3"]

-- Provides first guess
-- Takes no input arguements
-- Returns a pair of an initial guess and game state
initialGuess :: ([String], GameState)
initialGuess = (firstGuess, chordCombinations)

-- Takes as input a pair of previous guess and game state,
-- and the feedback to this guess as a triple of correct pitches, notes,
-- octaves, and returns a pair of the next guess and game state
nextGuess :: ([String], GameState) -> Score -> ([String], GameState)
nextGuess (target, currentGameState) score = (guess, newGameState)
    where guess        = maxBestGuess newGameState
          newGameState = filterList currentGameState target score

-- Produces the best guess by applying hint 3
-- Takes the maximum best target available by folding over the list of 
-- remaining target candidates and accumulating the best guess in a tuple
-- Takes in a game state
-- Returns the best guess
maxBestGuess :: GameState -> [String]
maxBestGuess gameState = bestGuess
    where bestGuess = snd $ foldr search acc gameState
          acc = (length chordCombinations, [])
          search target acc
              | fst acc > len = (len, target)
              | otherwise = acc
              where len = maxGroupTargets target gameState

-- Finds the maximum target from a group
-- Takes in a list of strings and a game state
-- Returns the maximum length of a group of targets
maxGroupTargets :: [String] -> GameState -> Int
maxGroupTargets target gameState = max' lenList
    where max' [] = 0
          max' xs = maximum xs
          groupedList = groupTargets target gameState
          lenList = [length x | x <- groupedList]

-- Groups targets by scores
-- Sorts groups in reverse order to improve efficiency
-- Takes in a list of strings and a game state
-- Returns a nested list of grouped scores
groupTargets :: [String] -> GameState -> [[Score]]
groupTargets target gameState = group $ sortBy (comparing Down) xs
    where xs = [response target x | x <- gameState]

-- Removes duplicate items in list
-- Takes in a list
-- Returns a list without duplicates
-- Acts similar to the 'nub' function in Data.List
uniqueElements :: (Eq a) => [a] -> [a]
uniqueElements [] = []
uniqueElements (x:xs) = x : uniqueElements nextList
    where nextList = [y | y <- xs, y /= x]

-- Returns mutual elements between two lists
-- Takes in two lists
-- Returns a list with common elements
-- Acts the same as 'intersect' from Data.List
mutualElements :: (Eq a) => [a] -> [a] -> [a]
mutualElements [] _ = []
mutualElements _ [] = []
mutualElements (x:xs) ys
    | x `elem` ys = x : mutualElements xs ys
    | otherwise = mutualElements xs ys

-- Determines which part of a Musical note is to be compared
-- Returns Truenif both components(pitch, note, octave) are 
-- the same, False otherwise
-- Takes in a Musical type, two lists
-- Returns Boolean
equality :: (Eq a) => MusicalType -> [a] -> [a] -> Bool
equality cmp xs ys
    | cmp == Note = xs !! 0 == ys !! 0
    | cmp == Octave = xs !! 1 == ys !! 1
    | otherwise = xs == ys

-- Computes the correct answer to a guess
-- Takes in two list of strings
-- Returns a tuple of scores
response :: [String] -> [String] -> Score
response target guess = (pitches, notes ,octaves)
    where distinctList   = uniqueElements target
          lengthDistinct = length $ distinctList
          lenNotes       = length $ deleteFirstsBy (equality Note) 
                                    distinctList guess
          lenOctaves     = length $ deleteFirstsBy (equality Octave)
                                    distinctList guess
          pitches        = length $ mutualElements distinctList guess
          notes          = lengthDistinct - lenNotes - pitches
          octaves        = lengthDistinct - lenOctaves - pitches

-- Filters down a list checking all possible targets
-- Looks at the current feedback score, and compares it with
-- previous feedback score and determines if a target should
-- remain in the current game state
-- Takes in a game state, list of strings, and score tuple
-- Returns a new game state
filterList :: GameState -> [String] -> Score -> GameState
filterList [] _ _ = []
filterList (x:xs) ys scores
    | scores == currentFeedback = x : filterList xs ys scores
    | otherwise = filterList xs ys scores
    where currentFeedback = response x ys



