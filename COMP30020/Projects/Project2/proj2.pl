% libraries loaded
:- ensure_loaded(library(clpfd)).

% Puzzle solver
puzzle_solution(Puzzle) :-
    Puzzle = [_|T],
    check_diagonal(T),
    maplist(is_valid_heading, T),
    transpose(Puzzle, [_|T2]),
    maplist(is_valid_heading, T2).

% Checks if puzzle has same diagonal values
check_diagonal(X) :-
    add_diagonal(X, 1, Y), 
    all_same(Y).

% Creates a list of all the diagonal values
add_diagonal([], _, []).
add_diagonal([X|Xs], I, Y) :-
    nth0(I, X, E),
    I1 is I + 1,
    append([E], R, Y),
    add_diagonal(Xs, I1, R).

% Checks if a heading holds the sum of product of the given
% row or column
is_valid_heading([X|Xs]) :-
    check_range(Xs),
    check_repeats(Xs),
    (
        sum_list(Xs, X)
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

% Checks product of header
product(A, B, P) :- P is A * B.
check_product(Xs, P) :- foldl(product, Xs, 1, P).

% Checks if all elements are equal
all_same([]).   
all_same([_]).
all_same([X, X|T]) :- 
    all_same([X|T]).

