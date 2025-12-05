% To run the solver, query:
% ?- solve_two_four(Vars).

:- use_module(library(clpfd)).

solve_two_four([T,W,O,F,O2,U,R]) :-
    Vars = [T,W,O,F,O2,U,R],
    Vars ins 0..9,
    all_different(Vars),

    % Leading letters cannot be zero
    T #\= 0,
    F #\= 0,

    % TWO + TWO = FOUR (with carries)
    %     T W O
    %   + T W O
    % -------------
    %   F O2 U R

    % Column-wise equations (right to left)
    O + O #= R + 10*C1,
    W + W + C1 #= U + 10*C2,
    T + T + C2 #= O2 + 10*C3,
    C3 #= F,   % Last carry becomes F

    labeling([ff], Vars),
    print_solution2(Vars).

print_solution2([T,W,O,F,O2,U,R]) :-
    TWO   is 100*T + 10*W + O,
    FOUR  is 1000*F + 100*O2 + 10*U + R,
    Result is TWO + TWO,
    nl,
    format("T = ~d, W = ~d, O = ~d~n", [T,W,O]),
    format("F = ~d, O2 = ~d, U = ~d, R = ~d~n", [F,O2,U,R]),
    nl,
    format("TWO  = ~d~n", [TWO]),
    format("TWO + TWO = ~d~n", [Result]),
    format("FOUR = ~d~n", [FOUR]),
    nl.

