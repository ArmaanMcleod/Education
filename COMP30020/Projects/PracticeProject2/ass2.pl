% Question 1
% correspond(E1, L1, E2, L2)
correspond(X, [X|_], Y, [Y|_]).
correspond(E1, [_|Xs], E2, [_|Ys]) :-
    correspond(E1, Xs, E2, Ys).

% Question 2
% interleave(Ls, L)
interleave([], []).
interleave([L|Ls], L) :-
    interleave(Ls, T),
    append(L, T, )

    



