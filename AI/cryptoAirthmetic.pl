% Lab 7
% TITLE: Cryptoartithmetic puzzel using CSP
% OBJECTIVE:
% To solve Cryptoartithmetic problem SEND + MORE = MONEY using constraint logic programming in prolog

:- use_module(library(clpfd)).

solve_compact([S,E,N,D,M,O,R,Y]) :-
    Vars = [S,E,N,D,M,O,R,Y],
    Vars ins 0..9,
    all_different(Vars),
    S #\= 0,
    M #\= 0,
    1000*S + 100*E + 10*N + D
  + 1000*M + 100*O + 10*R + E
  #= 10000*M + 1000*O + 100*N + 10*E + Y,
    labeling([ff], Vars).

solve_carry([S,E,N,D,M,O,R,Y]) :-
    Digits  = [S,E,N,D,M,O,R,Y],
    Carries = [C1,C2,C3,C4],
    Digits ins 0..9,
    Carries ins 0..1,
    all_different(Digits),
    S #\= 0,
    M #\= 0,
    D + E       #= Y + 10*C1,
    N + R + C1  #= E + 10*C2,
    E + O + C2  #= N + 10*C3,
    S + M + C3  #= O + 10*C4,
    C4 #= M,
    labeling([ff], Digits).

print_solution([S,E,N,D,M,O,R,Y]) :-
    SEND  is 1000*S + 100*E + 10*N + D,
    MORE  is 1000*M + 100*O + 10*R + E,
    MONEY is 10000*M + 1000*O + 100*N + 10*E + Y,
    nl,
    format("S = ~d, E = ~d, N = ~d, D = ~d~n", [S,E,N,D]),
    format("M = ~d, O = ~d, R = ~d, Y = ~d~n", [M,O,R,Y]),
    nl,
    format("SEND  = ~d~n", [SEND]),
    format("MORE  = ~d~n", [MORE]),
    format("MONEY = ~d~n", [MONEY]),
    nl.