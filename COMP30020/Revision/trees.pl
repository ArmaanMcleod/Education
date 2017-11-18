inset_member(N, tree(_, N, _)).
inset_member(N, tree(L, N0, _)) :-
    N < N0,
    inset_member(N, L).
inset_member(N, tree(_, N0, R)) :-
    N > N0,
    inset_member(N, R).

intset_insert(N, empty, tree(empty,N,empty)).
intset_insert(N, tree(L,N,R), tree(L,N,R)).
intset_insert(N, tree(L0,N0,R), tree(L,N0,R)) :-
        N < N0,
        intset_insert(N, L0, L).
intset_insert(N, tree(L,N0,R0), tree(L,N0,R)) :-
        N > N0,
        intset_insert(N, R0, R).

tree(Empty).
tree(node(Left, _, Right)) :-
    tree(Left),
    tree(Right).

tree_list(empty, []).
tree_list(node(Left, Elt, Right), List) :-
    tree_list(Right, List1),
    tree_list(Left, List2),
    append(List1, [Elt|List2], List).

tree_list1(Tree, List) :-
    tree_list1(Tree, [], List).

tree_list1(empty, List, List).
tree_list1(node(Left, Elt, Right), )
    
