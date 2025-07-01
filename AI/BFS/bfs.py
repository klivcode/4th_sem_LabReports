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


def bfs(graph, start, goal):
    visited = []
    queue = [start]
    step = 0

    # print table header
    print("\n BFS Fringe Tracking in Table")
    print("Step      | Node       | Fringe(Queue)                  | Visited")
    print("-" * 60)

    # BFS Traversal
    while queue:
        node = queue.pop(0) #take the front node
        step += 1
        if node not in visited:
            visited.append(node)
            print_table_row(step, node, queue, visited)

            if node == goal:
                print(f"\n Goal {goal} found with {step} steps!")
                break

            # enqueue children from left to right
            for child in graph[node]:
                if child not in visited and child not in queue:
                    queue.append(child)







# set the start and goal nodes
start_node = 'A'
goal_node = 'K'



# run bfs
bfs(graph, start_node, goal_node)


