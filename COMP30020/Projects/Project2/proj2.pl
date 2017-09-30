% libraries loaded
:- ensure_loaded(library(clpfd)).

% 2 x 2 Solver
puzzle_solution([[_, C1, C2], [R1, R11, R12], [R2, R21, R22]]) :-
    R11 = R22,
    is_valid_heading([R1, R11, R12]),
    is_valid_heading([R2, R21, R22]),
    is_valid_heading([C1, R11, R21]),
    is_valid_heading([C2, R12, R22]).



% Checks if a heading holds the sum of product of the given
% row or column
is_valid_heading([X|Xs]) :-
    check_range(Xs),
    check_repeats(Xs),
    (
        check_sums([X|Xs])
    ;   
        check_product(Xs, X)
    ).

% Checks ranges of numbers in a list
% Returns True if between 1 and 9
check_range([]).
check_range([X|Xs]) :-
   L is 1,
   H is 9,
   between(L, H, X),
   check_range(Xs).

% Checks repeated elements in list
check_repeats(Xs) :- all_different(Xs).

% Checks sum of header
check_sums([X|Xs]) :- sum_list(Xs, X).

% Checks product of header
product(A, B, P) :- P is A * B.
check_product(Xs, P) :- foldl(product, Xs, 1, P).

