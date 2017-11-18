data Heap a = Empty | Node a (Heap a) (Heap a)

remove_biggest :: (Ord a) => Heap a -> (a, Heap a)
remove_biggest (Node x l r)
    


