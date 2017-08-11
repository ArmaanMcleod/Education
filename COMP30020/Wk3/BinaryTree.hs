{-Binary Search Tree 

	C implementation

	typedef struct bst_struct *BST
	struct bst_struct {
		char *key;
		int value;
		BST left;
		BST right;
	}
-}

data Tree = Leaf | Node String Int Tree Tree

--maybe a tree, maybe nothing

countnodes :: Tree -> Int
countnodes Leaf = 0
countnodes (Node _ _ l r) = 1 + countnodes(l) + countnodes(r)

search_bst :: Tree -> String -> Maybe Int
search_bst Leaf _ = Nothing
search_bst (Node k v l r) sk
    | sk == k = Just v
    | sk < k = search_bst l sk
    | otherwise = search_bst r sk

filterlist :: (Num a) => [a] -> [a]
filterlist [] = []
filterlist (x:xs)
    | x >= 0 = x : filterlist xs
    | otherwise = filterlist xs



