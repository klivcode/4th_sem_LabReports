'''
Lab 2 (Python): DFS and BFS Search Algorithms
Objective:
To implement Depth-First Search (DFS) and Breadth-First Search (BFS) algorithms in Python.
To explore the differences between DFS and BFS in terms of their approach to searching and traversing data structures.
To apply these algorithms to solve problems such as pathfinding in mazes and graph traversal.




A
├── B
│   ├── D
│   │   ├── H
│   │   └── K
│   └── E
├── C
│   ├── F
│   │   └── J
│   └── G


'''

# Define the tree using nested dictionaries
graph = {
    'A': ['B', 'C'],
    'B': ['D', 'E'],
    'C': ['F', 'G'],
    'D': ['H', 'K'],
    'E': ['J'],
    'F': [],
    'G': [],
    'H': [],
    'K': [],
    'I': [],
    'J': [],
    'K': [],
}

# Function to print the value in table format
def print_table_row(step, node, fringe, visited):
    print(f"{step:<5} | {node:<10} | {str(fringe):<25} | {str(visited)}")


# Depth-First Search (DFS) algorithm
def dfs(graph, start, goal):
    stack = [start]
    visited = []
    step = 0
    
    
    # print table header
    print("\n DFS fringe Tracking in Table")
    print("Step | Node       | Fringe                   | Visited")
    print("-" * 50)
    
    #DFS Traversal
    while stack:
        node=stack.pop()
        step += 1
        if node not in visited:
            visited.append(node)
            
            #display the current  search space
            print_table_row(step, node, stack[::-1], visited)
        
        if node == goal:
            print(f"\nGoal node '{goal}' found after {step} steps.")
            break
         
         # backtrack if node is not the goal
        for child in reversed(graph[node]):
            if child not in visited:
                stack.append(child)

# set the start and goal nodes
start_node = 'A'
goal_node = 'K'

# Run DFS
dfs(graph, start_node, goal_node)


