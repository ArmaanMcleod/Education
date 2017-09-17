is_list([]).
is_list([_|T]) :-
    is_list(T).

correspond(E1, [X|Xs], E2, [Y|Ys]) :-
    is_list([X|Xs]),
    is_list([Y|Ys]),
    ( E1 == X ->
        E2 is Y,
        correspond(E1, Xs, E2, Ys)
    ).

    





