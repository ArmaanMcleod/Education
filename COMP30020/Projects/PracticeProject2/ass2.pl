% Question 1
% correspond(E1, L1, E2, L2)
correspond(X, [X|_], Y, [Y|_]).
correspond(E1, [_|Xs], E2, [_|Ys]) :-
    correspond(E1, Xs, E2, Ys).

% Question 2
% interleave(Ls, L)

equal_lengths([]).
equal_lengths([[]]).
equal_lengths([[_|_]]).
equal_lengths([X,Y|Rest]) :- 
  length(X, Len), 
  length(Y, Len), 
  equal_lengths([Y|Rest]).

interleave([[] | T], X) :-
    equal_lengths(T),
    interleave(T, X).

interleave([], []).
interleave([[H|T]|X], [H|Y]) :-
    append(X, [T], X2),
    interleave(X2, Y).


map(_, [], []).
map(P, [X|Xs], [Y|Ys]) :-
    call(P, X, Y),
    map(P, Xs, Ys).

filtered(_, [], []).
filtered(P, [X|Xs], Result) :-
    (call(P, X) ->
        Result = [X|Tail]
    ;
        Result = Tail
    ),
    filtered(P, Xs, Tail).

