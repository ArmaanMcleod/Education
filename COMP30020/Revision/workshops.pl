% Workshop 7
list_of(_, []).
list_of(Elt, [Elt|Rest]) :-
    list_of(Elt, Rest).

all_same([]).
all_same([_]).
all_same([X, X|Xs]) :-
    all_same([X|Xs]).

adjacent1(E1, E2, List) :-
    append(_, [E1, E2|_], List).

adjacent2(E1, E2, [E1, E2|_]).
adjacent2(E1, E2, [_|Rest]) :-
    adjacent2(E1, E2, Rest).

before(E1, E2, [E1|Rest]) :-
    member(E2, Rest).
before(E1, E2, [_|Rest]) :-
    before(E1, E2, Rest).

% Binary tree stuff
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

% Workshop 8
sumlist([], 0).
sumlist([X|Xs], Sum) :-
    sumlist(Xs, Sums),
    Sum is X + Sums.

sumlist1(X, Sum) :-
    sumlist2(X, 0, Sum).

sumlist2([], Sum, Sum).
sumlist2([X|Xs], Acc, Sum) :-
    Sum1 is Acc + X,
    sumlist2(Xs, Sum1, Sum).

tree(empty).
tree(node(Left, _, Right)) :-
    tree(Left),
    tree(Right).

tree_list(empty, []).
tree_list(node(Left, Elt, Right), List) :-
    tree_list(Left, List1),
    tree_list(Right, List2),
    append(List1, [Elt|List2], List).

tree_list1(Tree, List) :-
    tree_list2(Tree, List, []).

tree_list2(empty, List, List).
tree_list2(node(Left, Elt, Right), List, AccList) :-
    tree_list2(Left, List, List1),
    List1 = [Elt|List2],
    tree_list2(Right, List2, AccList).

list_tree([], empty).
list_tree([X|List], node(Left, Elt, Right)) :-
    length(List, Len),
    Len2 is Len // 2,
    length(Front, Len2),
    append(Front, [Elt|Back], [X|List]),
    list_tree(Front, Left),
    list_tree(Back, Right).

% Workshop 9

same_Elements([], _).
same_Elements([X|Xs], Ys) :-
    msort(Ys, Sorted),
    member(X, Sorted),
    same_Elements(Xs, Sorted).

same_Elements(_, []).
same_Elements(Xs, [Y|Ys]) :-
    msort(Xs, Sorted),
    member(Y, Sorted),
    same_Elements(Sorted, Ys).

times(W, X, Y, Z) :-
    (
        (
            integer(W);
            integer(Y);
            integer(Z)
        ),

        (
            integer(Z),
            integer(W);
            integer(Z),
            integer(Y)
        )
    ),

    (   Y >= 0,
        W > Y
    ;
        Y > W,
        Y =< 0
    ),

    (W * X) + Y is Z.

mydrop(N, [X|Xs], Back) :-
    (N = 0 ->
        append([X], Xs, Back)
    ;
        N0 is N - 1,
        mydrop(N0, Xs, Back)
    ).


multiply(X, Y, XY) :-
    multiply1(X, Y, 0, XY).

multiply1(X, Y, A, XY) :-
    (X = 0 ->
        XY = A
    ; 
        X1 is X - 1,
        A1 is A + Y,
        multiply1(X1, Y, A1, XY)
    ).

filter(_, [], []).
filter(P, [X|Xs], Filtered) :-
    (call(P, X) ->
        Filtered = [X|Filtered1]
    ;
        Filtered = Filtered1
    ),
    filter(P, Xs, Filtered1).

map(_, [], []).
map(P, [X|Xs], [Y|Ys]) :-
    call(P, X, Y),
    map(P, Xs, Ys).


sort_sublists([], []).
sort_sublists([X|Xs], List) :-
    (integer(X) ->
        List = [X | List1]
    ;
        sort(X, Sorted),
        List = [Sorted | List1]
    ),
    sort_sublists(Xs, List1).
