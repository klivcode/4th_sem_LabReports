

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
    'J': []
}


def bfs_from_node(graph, start):
    visited = []
    queue = [start]
    levels = {start: 0}      # store BFS level for each node

    print(f"\n=== BFS Traversal Starting from {start} ===")

    while queue:
        node = queue.pop(0)
        visited.append(node)

        # explore neighbors
        for child in graph[node]:
            if child not in visited and child not in queue:
                queue.append(child)
                levels[child] = levels[node] + 1

    # Print layer-wise groups
    print("\n=== Layer-wise Traversal ===")
    layer_groups = {}

    for node, lvl in levels.items():
        layer_groups.setdefault(lvl, []).append(node)

    for lvl in sorted(layer_groups.keys()):
        print(f"Level {lvl}: {layer_groups[lvl]}")

    print("\n=== Nodes Reachable from", start, "===")
    print(visited)

    print("\n=== Final BFS Order ===")
    print(" → ".join(visited))


# Run BFS from node C
bfs_from_node(graph, 'C')
