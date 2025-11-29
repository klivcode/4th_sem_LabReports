
'''
Lab 5
Title : Implememntation of N-quen Problem as CSP

(Domain,vaariable and constrainsts)


OBjective:
-> To implement N - Queen problem  using backtracing


'''


#function for printing the solution

def print_solution(board):
    n= len(board)
    for row in range(n):
        for col in range(n):
            print ("Q" if board [row]== col else " .", end="")
        print("\n "+ "=" *(3*n) + "\n")
        
    
    
    
# check if queen attack each other

def is_safe(board, row,col):
    #check for row , coloumn and diagonal conflict
    for r in range(row):
        if board[r]== col or abs(board[r]-col)== abs(r-row):
            return False
    return True
    
#place the queen backtracking

def solve_n_queen(board,row,n,solution):
    #place queen row by row if the position is not safe 
    
    if row == n:
        solution.append(board[:]) # to save the solution
        return
    for col in range(n):
        if is_safe(board,row,col):
            board[row]= col
            solve_n_queen(board,row+1,n,solution)
            
            board[row]= -1 # backtracking
            
            
#min function

def n_queen(n):
    board=[-1]*n # -1 represents there is no queen
    solution=[]
    solve_n_queen(board,0,n,solution)
    
    return solution



if __name__=="__main__":
    N=4
    print(f"Solving {N} -Queen Problems \n")
    result= n_queen(N)
    
    print(f"Total solution found: {len(result)}\n")
    
    for i,sol in enumerate(result,1):
        print(f"Solution{i}:")
        print_solution(sol)


