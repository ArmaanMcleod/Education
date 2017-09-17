list_of(Elt, [Elt]).
list_of(Elt, [Elt|T]) :-
    list_of(Elt,T).

all_same([]).
all_same([H|T]) :-
    list_of(H, [H|T]).

adjacent(E1, E2, [E1, E2 | _]).
adjacent(E1, E2, [_|T]) :-
    adjacent(E1, E2, T).

proper_list([]).
proper_list([_Head|Tail]) :-
    proper_list(Tail).

