% AI/parentFamily.pl
% Lab 6
% TITLE: Predicate Logic and family tree

% OBJECTIVE:
   % -> To represent predicate logic in prolog
   % -> To implemement family relatiosnhip like parent, sibling, ancestor using facts and rules


% -- Family Facts --

% Parent relatiosnhip
parent(dasharath,ram).
parent(dasharath,laxman).
parent(dasharath,bharat).
parent(dasharath,shatrughan).

% Marriage
married(ram,sita).

% gender
male(ram).
male(laxman).
male(dasharath).
male(shatrughan).
male(bharat).
female(sita).

% --rules --
father(X,Y) :- parent(X,Y),male(X).
mother(X,Y) :- parent(X,Y),female(X).
sibling(X,Y) :- parent(P,X), parent(P,Y), X\=Y.
husband(X,Y) :- married(X,Y), male(X).
wife(X,Y) :- married(X,Y), female(X).

