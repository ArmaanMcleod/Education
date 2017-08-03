data Point = Pt Float Float

goodPoint :: Point -> Bool
goodPoint (Pt x y) = x > 0 && y > 0