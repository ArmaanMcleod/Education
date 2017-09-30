% libraries loaded
:- ensure_loaded(library(clpfd)).

% 2 x 2 Solver
puzzle_solution([[_, R02, R03], 
               [R11, R12, R13], 
               [R21, R22, R23]]) :-

    is_equal(R12, R23),
    is_valid_heading([R11, R12, R13]),
    is_valid_heading([R21, R22, R23]),
    is_valid_heading([R02, R12, R22]),
    is_valid_heading([R03, R13, R23]).

% 3 x 3 Solver
puzzle_solution([[_, R02, R03, R04],
               [R11, R12, R13, R14],
               [R21, R22, R23, R24],
               [R31, R32, R33, R34]]) :-

    is_equal(R12, R23), 
    is_equal(R23, R34),
    is_valid_heading([R11, R12, R13, R14]),
    is_valid_heading([R21, R22, R23, R24]),
    is_valid_heading([R31, R32, R33, R34]),
    is_valid_heading([R02, R12, R22, R32]),
    is_valid_heading([R03, R13, R23, R33]),
    is_valid_heading([R04, R14, R24, R34]).

% 4 x 4 Solver
puzzle_solution([[_, R02, R03, R04, R05],
               [R11, R12, R13, R14, R15],
               [R21, R22, R23, R24, R25],
               [R31, R32, R33, R34, R35],
               [R41, R42, R43, R44, R45]]) :-

    is_equal(R12, R23),
    is_equal(R23, R34),
    is_equal(R34, R45),
    is_valid_heading([R11, R12, R13, R14, R15]),
    is_valid_heading([R21, R22, R23, R24, R25]),
    is_valid_heading([R31, R32, R33, R34, R35]),
    is_valid_heading([R41, R42, R43, R44, R45]),
    is_valid_heading([R02, R12, R22, R32, R42]),
    is_valid_heading([R03, R13, R23, R33, R43]),
    is_valid_heading([R04, R14, R24, R34, R44]),
    is_valid_heading([R05, R15, R25, R35, R45]).


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

% Checks if two elements are equal.
is_equal(X, Y) :- X = Y.

