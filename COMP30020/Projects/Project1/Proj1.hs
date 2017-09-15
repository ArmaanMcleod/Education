--  File           : Proj1.hs
--  Author         : Armaan Dhaliwal-McLeod
--  Student Number : 837674
--  Subject        : COMP30020 Declarative Programming

{- 
  This project was programmed by myself, and was Project 1 for Declaratative
  Programming. Main purpose of this program is to create a guessing game
  for ChordProbe. The aim is to achieve the least amount of guesses to 
  guesses the correct target. This code aims to achieve a lower average
  of guesses to achieve a certain target. 
 -}

-- Module declaration
module Proj1 (initialGuess, nextGuess, GameState) where

-- Libraries used in this module
import Data.List 

-- Game State type
-- Used for storing previous targets
type GameState = [[String]]

-- Score type
-- Used for giving the triple score a meaningful name
type Score = (Int, Int, Int)

-- data type for components of a Musical note
data MusicalType = Pitch | Note | Octave
    deriving (Eq, Show, Ord)

-- Constant symbolizing number of pitches in a musical note
_NUMPITCHES= 3

-- Produces all possible pitches
-- Takes in two lists of strings
-- Returns a list of strings
-- E.g ["A1", "A2", "A3", "B1", ...]
pitchCombinations :: [String] -> [String] -> [String]
pitchCombinations xs ys = [x ++ y | x <- xs, y <- ys]

-- Credit https://wiki.haskell.org/99_questions/Solutions/26
-- Inspiration taken from here, code written by me 
-- Produces all possible combinations of pitches
-- Takes in a integer 'k', and list of strings
-- Returns a game state type of all 'k' combinations
allCombinations :: Int -> [String] -> GameState
allCombinations _ [] = [[]]
allCombinations 0 _ = [[]]
allCombinations k (x:xs) = start ++ others
    where start = [x : rest | rest <- leftovers (k-1) xs]
          leftovers = allCombinations
          others
              | k <= length xs = leftovers k xs
              | otherwise = []
    
-- Similar to 'pitchCombinations'
-- This function is more convenient to call
-- Calls function only using constant 'numPitches' as value for n
-- Takes in no arguements
-- Returns a game state, 1330 targets
chordCombinations :: GameState
chordCombinations = allCombinations _NUMPITCHES $ 
                    pitchCombinations notes octaves
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
-- Returns the best guess, the second tuple element accumulated
maxBestGuess :: GameState -> [String]
maxBestGuess gameState = bestGuess
    where bestGuess = snd $ foldr searchMax acc gameState
          acc = (length chordCombinations, [])
          searchMax target acc
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
-- Sorts groups to improve efficiency
-- Takes in a list of strings and a game state
-- Returns a nested list of grouped scores
groupTargets :: [String] -> GameState -> [[Score]]
groupTargets target gameState = group $ sort xs
    where xs = [response target x | x <- gameState]

-- Determines which part of a Musical note is to be compared
-- Returns True if both components(pitch, note, octave) are 
-- the same, False otherwise
-- Takes in a Musical type, two lists
-- Returns Boolean
-- Takes in a guess and a target
-- Returns a tuple of scores
-- NOTE: I used my own function which 
response :: [String] -> [String] -> Score

equality :: (Eq a) => MusicalType -> [a] -> [a] -> Bool
equality cmp xs ys
    | cmp == Note = xs !! 0 == ys !! 0
    | cmp == Octave = xs !! 1 == ys !! 1
    | otherwise = xs == ys

-- Computes the correct answer to a guess
response target guess    = (pitches, notes ,octaves)
    where distinctList   = nub target
          lengthDistinct = length distinctList
          lenNotes       = lengthScore Note distinctList guess
          lenOctaves     = lengthScore Octave distinctList guess
          pitches        = lengthScore Pitch distinctList guess
          notes          = lengthDistinct - lenNotes - pitches
          octaves        = lengthDistinct - lenOctaves - pitches

-- Computes lengths of lists, depending on musical type given
-- Takes in a musical type, a list of distinct notes, and a guess
-- Returns an integer representing the length og the list with
-- unique elements contained
lengthScore :: MusicalType -> [String] -> [String] -> Int
lengthScore cmp distinctList guess
    | (cmp == Note) || (cmp == Octave) = noteOctaveLen
    | otherwise = pitchLen
    where 
          pitchLen      = length $ intersect distinctList guess
          noteOctaveLen = length $ deleteFirstsBy (equality cmp) 
                                   distinctList guess

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



