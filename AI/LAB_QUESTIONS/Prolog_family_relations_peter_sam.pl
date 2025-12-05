

% ----------------------------------
% FAMILY FACTS  
% ----------------------------------

% parent relationships
parent(john, peter).
parent(john, sam).
parent(mary, peter).
parent(mary, sam).

parent(david, john).
parent(susan, john).

% marriage facts
married(john, mary).
married(mary, john).   % make marriage symmetric

% gender facts
male(john).
male(peter).
male(sam).
male(david).

female(mary).
female(susan).

% ----------------------------------
% RULES  
% ----------------------------------

% parent(X,Y): already defined as facts

% child(Y,X): Y is child of X
child(C, P) :- parent(P, C).

% husband
husband(H, W) :- married(H, W), male(H).

% wife
wife(W, H) :- married(W, H), female(W).

% father
father(F, C) :- parent(F, C), male(F).

% mother
mother(M, C) :- parent(M, C), female(M).

% sibling (common parent)
sibling(X, Y) :- parent(P, X), parent(P, Y), X \= Y.

% brother
brother(B, X) :- sibling(B, X), male(B).

% sister
sister(S, X) :- sibling(S, X), female(S).

% grandparent
grandparent(G, C) :- parent(G, P), parent(P, C).

% grandfather
grandfather(G, C) :- grandparent(G, C), male(G).

% grandmother
grandmother(G, C) :- grandparent(G, C), female(G).

% spouse (husband or wife)
spouse(X, Y) :- married(X, Y).
spouse(X, Y) :- married(Y, X).
