{-Using the definition of the Point type from the previous slide, 
  define a function goodPoint which takes a Point and returns True if it's in the first quadrant*
  of the Cartesian plane, and False otherwise.

  For example:


  Main> goodPoint (Pt 3.1 6.2)
  True
  Main> goodPoint (Pt 0.0 1.4)
  False
  Main> goodPoint (Pt (-1.0) 5)
  False
  * Remember that the 'first quadrant' is the region of the Cartesian plane where x and y coordinates are both positive.
-}

data Point = Pt Float Float

goodPoint :: Point -> Bool
goodPoint (Pt x y) = x > 0 && y > 0