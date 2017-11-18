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