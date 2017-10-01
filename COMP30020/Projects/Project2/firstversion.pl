% libraries loaded
:- ensure_loaded(library(clpfd)).

% 2 x 2 Solver
puzzle_solution(Puzzle) :-
    (
        length(Puzzle, 3),
        diagonal_2_by_2(Puzzle)
    ;
        length(Puzzle, 4),
        diagonal_3_by_3(Puzzle)
    ;
        length(Puzzle, 5),
        diagonal_4_by_4(Puzzle)
   ),

    Puzzle = [_|T],
    maplist(is_valid_heading, T),
    transpose(Puzzle, [_|T2]),
    maplist(is_valid_heading, T2).

diagonal_2_by_2([[_, _, _],
                 [_, R12, _],
                 [_, _, R23]]) :-
    all_same([R12, R23]).

diagonal_3_by_3([[_, _, _, _],
                 [_, R12, _, _],
                 [_, _, R23, _],
                 [_, _ ,_, R34]]) :-
    all_same([R12, R23, R34]).

diagonal_4_by_4([[_, _, _, _, _],
                 [_, R12, _, _, _],
                 [_, _, R23, _, _],
                 [_, _, _, R34, _],
                 [_, _, _, _, R45]]) :-
    all_same([R12, R23, R34, R45]).

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

% Checks if all elements are equal
all_same([]).   
all_same([_]).
all_same([X, X|T]) :- all_same([X|T]).