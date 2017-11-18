data Ttree t = Nil | Node3 t (Ttree t) (Ttree t) (Ttree t)

avg_num :: Ttree Double -> Double
avg_num Nil = 0.0
avg_num tree = go tree 0.0
    where go Nil acc = acc
          go (Node3 x l m r) acc = go l (acc + x) + go m acc + go r acc

size_tree :: Ttree Double -> Int
size_tree Nil = 0
size_tree (Node3 x l m r) = 1 + size_tree l + size_tree m + size_tree r

ttreAverage :: Ttree Double -> Double
ttreAverage Nil = 0.0
ttreAverage tt = 
    let (sum, count) =  ttAverage tt
    in sum / count

ttAverage :: Ttree Double -> (Double, Double)
ttAverage Nil = (0.0, 0.0)
ttAverage (Node3 x l m r) = 
    let (suml, countl) = ttAverage l
        (summ, countm) = ttAverage m
        (sumr, countr) = ttAverage r
    in (x + suml + summ + sumr, 1 + countl + countm + countr)