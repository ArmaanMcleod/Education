def unify_diagonals(lst):
    return len(set([lst[i][i] for i in range(len(lst))])) == 1

 
