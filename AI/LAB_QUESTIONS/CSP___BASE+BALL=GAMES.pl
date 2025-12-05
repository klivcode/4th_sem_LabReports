

% To run the solver, query:
% ?- solve_base_ball_games(Vars).


:- use_module(library(clpfd)).

solve_base_ball_games([B,A,S,E,L,G,M]) :-
    Vars = [B,A,S,E,L,G,M],
    Vars ins 0..9,
    all_different(Vars),

    B #\= 0,
    G #\= 0,

    BASE  #= 1000*B + 100*A + 10*S + E,
    BALL  #= 1000*B + 100*A + 10*L + L,
    GAMES #= 10000*G + 1000*A + 100*M + 10*E + S,

    BASE + BALL #= GAMES,

    labeling([ff], Vars),
    print_solution([B,A,S,E,L,G,M]).

print_solution([B,A,S,E,L,G,M]) :-
    BASE  is 1000*B + 100*A + 10*S + E,
    BALL  is 1000*B + 100*A + 10*L + L,
    GAMES is 10000*G + 1000*A + 100*M + 10*E + S,
    nl,
    format("B=~d A=~d S=~d E=~d L=~d G=~d M=~d~n", [B,A,S,E,L,G,M]),
    nl,
    format("BASE  = ~d~n", [BASE]),
    format("BALL  = ~d~n", [BALL]),
    format("GAMES = ~d~n", [GAMES]),
    nl.

