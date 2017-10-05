% Question 1
% Non tail recursive
sumlist1([], 0).
sumlist1([N|Ns], Sum) :-
    sumlist1(Ns, Sum0),
    Sum is N + Sum0.

% tail recursive
sumlist2(L, Sum) :-
    sumlist_acc(L, 0, Sum).

sumlist_acc([], Sum, Sum).
sumlist_acc([H|T], Acc, Sum) :-
    Acc1 is H + Acc,
    sumlist_acc(T, Acc1, Sum).

% Question 2
tree(empty).
tree(node(Left,_,Right)) :-
    tree(Left),
    tree(Right).

tree_list(Tree, List) :-
    tree_list_acc(Tree, [], List).

tree_list_acc(empty, List, List).
tree_list_acc(node(L, X, R), Acc, List) :-
    tree_list_acc(L, Acc, Acc1),
    append(Acc1, [V], Acc2),
    tree_list_acc(R, Acc2, List).

tree_list_app(empty, []).
tree_list_app(node(L, X, R), List) :-
    tree_list_app(L, List1),
    tree_list_app(R, List2),
    append(List1, [X|List2], List).

% Question 3
tree_list_rec(empty, []).
tree_list_rec(node(L, X, R), List) :-
    tree_list_rec(L, List1),
    tree_list_rec(R, List2),
    Acc1 
    append(List1, [X|List2], List).