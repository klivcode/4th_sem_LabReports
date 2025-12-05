% To run the solver, query:
% ?- solve_cross_road_danger(Solution).




:- use_module(library(clpfd)).

solve_cross_road_danger(Solution) :-
    % Variables for letters
    Vars = [C,R,O,S,A,D,N,G,E],
    Vars ins 0..9,
    all_different(Vars),

    % Leading digits cannot be zero
    C #\= 0,
    R #\= 0,
    D #\= 0,

    % WORD VALUES
    CROSS #= 10000*C + 1000*R + 100*O + 10*S + S,
    ROAD  #= 1000*R + 100*O + 10*A + D,
    DANGER #= 100000*D + 10000*A + 1000*N + 100*G + 10*E + R,

    CROSS + ROAD #= DANGER,

    labeling([ff], Vars),
    Solution = Vars,
    print_solution(Vars).

print_solution([C,R,O,S,A,D,N,G,E]) :-
    CROSS is 10000*C + 1000*R + 100*O + 10*S + S,
    ROAD  is 1000*R + 100*O + 10*A + D,
    DANGER is 100000*D + 10000*A + 1000*N + 100*G + 10*E + R,
    nl,
    format("C = ~d, R = ~d, O = ~d, S = ~d~n", [C,R,O,S]),
    format("A = ~d, D = ~d, N = ~d, G = ~d, E = ~d~n", [A,D,N,G,E]),
    nl,
    format("CROSS  = ~d~n", [CROSS]),
    format("ROAD   = ~d~n", [ROAD]),
    format("DANGER = ~d~n", [DANGER]),
    nl.

