fact1(N, F) :-
    (N =:= 0 ->
        F = 1
    ;   N > 0,
        N1 is N-1,
        fact1(N1, F1),
        F is F1 * N
    ).

fact2(N, F) :- fact(N, 1, F).
fact(N, A, F) :-
    ( N > 0,
        A1 is A * N,
        N1 is N - 1,
        fact(N1, A1, F)
    ; N =:= 0 ->
        F = A
    ).

multiply1(X, Y, XY) :-
    ( X = 0 ->
        XY = 0
    ;   X1 is X - 1,
        multiply1(X1, Y, X1Y),
        XY = X1Y + Y
    ).

multiply2(X, Y, XY) :- 
    multiply(X, Y, 0, XY).

multiply(X, Y, A, XYA) :-
    ( X = 0 ->
        XYA = A
    ;   X1 is X-1,
        A1 is A + Y,
        multiply(X1, Y, A1, XYA)
    ).

rev1([], []).
rev1([X|Xs], R) :-
    rev1(Xs, T),
    append(T, [X], R).

fibonacci(1, 0).
fibonacci(2, 1).
fibonacci(N, X) :-
    ( N > 2 ->
        N1 is N - 1,
        N2 is N - 2,
        fibonacci(N1, Result1),
        fibonacci(N2, Result2),
        X is Result1 + Result2
    ).

