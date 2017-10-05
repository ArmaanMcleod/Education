loves(romeo, juliet).

% :- same as if

loves(juliet, romeo) :-
    loves(romeo, juliet).

male(Albert).
male(John).
male(Alex).

female(Alice).
female(Diana).

happy(Albert).

runs(Albert) :-
    happy(Albert).