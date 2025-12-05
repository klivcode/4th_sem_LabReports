
graph = {
    'S': ['A', 'B'],
    'A': ['C', 'D'],
    'B': ['E'],
    'C': [],
    'D': [],
    'E': ['F'],
    'F': []
}

dfs_order = []
dfs_tree = {}   # store DFS tree edges


def dfs(graph, node, visited):
    visited.add(node)
    dfs_order.append(node)

    for child in graph[node]:
        if child not in visited:
            # store parent → child as DFS tree edge
            dfs_tree.setdefault(node, []).append(child)
            dfs(graph, child, visited)


def run_dfs(graph, start):
    visited = set()
    dfs(graph, start, visited)

    print("\n=== DFS Order ===")
    print(" → ".join(dfs_order))

    print("\n=== DFS Tree (Edges) ===")
    for parent, children in dfs_tree.items():
        for c in children:
            print(f"{parent} → {c}")

    print("\n=== DFS Tree Structure ===")
    print_dfs_tree(start, 0)


def print_dfs_tree(node, depth):
    print("   " * depth + node)
    if node in dfs_tree:
        for child in dfs_tree[node]:
            print_dfs_tree(child, depth + 1)


# Run DFS from S
run_dfs(graph, 'S')
