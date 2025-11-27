
# '''
# TITLE: Game search using Minimax algorithm

# Objective:
# * To implement minimax algorithm for two player game i.e Tic-Tac-Toe
# * To understand the concept of adversial search and decision making

# Algorithm:
# 1) Define reversible function
#     minimax(board,depth,isMaximizing)
# 2) If game is over then we need to return score (win, draw. lose)
# 3) If Maximizers turn:
#     --> Initialize best score to -infinity
#     --For each possible move:
#         * Make the move
#         * call minimax function recurssively with isMaximizing = Flase
#         * Undo the move
#         * Update the best score with maximum value
# 4) If Minimizers turn:
#      --> Initialize best score to -infinity
#     --For each possible move:
#         * Make the move
#         * call minimax function recurssively with isMaximizing = True
#         * Undo the move
#         * Update the best score with manimum value
# 5) Return the best score
# 6) The best score is returned on the basis of highest minimax score
# '''


import math

# initialize board
board = [" " for _ in range(9)]

# print the board
def print_board():
    for i in range(3):
        row = board[i*3:(i+1)*3]
        print("| " + " | ".join(row) + " |")
    print()

# check the winner
def check_winner(brd):
    win_combinations = [
        [0,1,2], [3,4,5], [6,7,8],  # rows
        [0,3,6], [1,4,7], [2,5,8],  # cols
        [0,4,8], [2,4,6]            # diagonals
    ]
    for combo in win_combinations:
        if brd[combo[0]] == brd[combo[1]] == brd[combo[2]] and brd[combo[0]] != " ":
            return brd[combo[0]]
    return None

# check for draw
def is_draw(brd):
    return " " not in brd

# minimax algorithm
def minimax(brd, depth, isMaximizing):
    winner = check_winner(brd)
    if winner == "O":  # AI wins
        return 1
    elif winner == "X":  # human wins
        return -1
    elif is_draw(brd):
        return 0

    if isMaximizing:
        bestscore = -math.inf
        for i in range(9):
            if brd[i] == " ":
                brd[i] = "O"
                score = minimax(brd, depth+1, False)
                brd[i] = " "
                bestscore = max(score, bestscore)
        return bestscore
    else:
        bestscore = math.inf
        for i in range(9):
            if brd[i] == " ":
                brd[i] = "X"
                score = minimax(brd, depth+1, True)
                brd[i] = " "
                bestscore = min(score, bestscore)
        return bestscore

# AI chooses the best move
def best_move(brd):
    bestscore = -math.inf
    move = None
    for i in range(9):
        if brd[i] == " ":
            brd[i] = "O"
            score = minimax(brd, 0, False)
            brd[i] = " "
            if score > bestscore:
                bestscore = score
                move = i
    if move is not None:
        brd[move] = "O"

# main game play
def play_game():
    print("Tic Tac Toe (You are X, AI is O)\n")
    print_board()

    while True:
        # Human move
        move = int(input("Enter your move (0-8): "))
        if board[move] == " ":
            board[move] = "X"
        else:
            print("Invalid move, try again.")
            continue

        print_board()

        if check_winner(board) == "X":
            print("You win!")
            break
        elif is_draw(board):
            print("It's a draw!")
            break

        # AI move
        best_move(board)
        print("AI plays:")
        print_board()

        if check_winner(board) == "O":
            print("AI wins!")
            break
        elif is_draw(board):
            print("It's a draw!")
            break

# Run the game
play_game()