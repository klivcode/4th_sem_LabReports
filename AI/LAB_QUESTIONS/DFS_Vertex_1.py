

graph = {
    1: [2, 3],
    2: [4, 5],
    3: [6],
    4: [],
    5: [],
    6: []
}


# Global list to maintain DFS order
dfs_order = []


def dfs(graph, node, visited, depth=0):
    indent = "    " * depth        # indentation for recursion display

    print(f"{indent}Entering DFS({node})")

    visited.add(node)
    dfs_order.append(node)

    # explore children
    for child in graph[node]:
        if child not in visited:
            print(f"{indent}→ Going deeper: {node} → {child}")
            dfs(graph, child, visited, depth + 1)
        else:
            print(f"{indent}→ Already visited {child}, skipping")

    print(f"{indent}Returning from DFS({node})")


def run_dfs(graph, start):
    visited = set()
    dfs(graph, start, visited)

    print("\n=== FINAL DFS ORDER ===")
    print(" → ".join(map(str, dfs_order)))


# Run DFS from vertex 1
run_dfs(graph, 1)
