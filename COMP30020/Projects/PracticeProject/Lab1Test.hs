--  File     : publictests.hs
--  Author   : Peter Schachte
--  Purpose  : test cases for Lab1 project

import Lab1
import HaskellTest

suite = 
  TimeLimit 2.0 $
  Suite [
    expect (subst 0 1 [0,1,2,3]) ([1,1,2,3]),
    expect (subst 'e' 'o' "dog") ("dog"),
    expect (subst 'e' 'o' "elephant") ("olophant"),

    expect (interleave [1,2,3,4] [11,12,13,14]) ([1,11,2,12,3,13,4,14]),
    expect (interleave "" "dog") ("dog"),
    expect (interleave "wl" "arus") ("walrus"),
    expect (interleave "tlpone" "eeh") ("telephone"),

    expect (unroll 3 [1,2,3,4,5]) ([1,2,3]),
    expect (unroll 8 [1,2,3]) ([1,2,3,1,2,3,1,2]),
    expect (unroll 4 "ski") ("skis")
    ]

main :: IO ()
main = do
  testVerbose suite
