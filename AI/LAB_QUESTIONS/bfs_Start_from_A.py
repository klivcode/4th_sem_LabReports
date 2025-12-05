

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


def bfs_levels(graph, start):
    visited = []
    queue = [start]
    levels = {}            # level dictionary
    current_level = 0

    # assign level for start node
    levels[start] = 0

    print("\n=== BFS LEVEL ORDER ===")

    while queue:
        node = queue.pop(0)

        if node not in visited:
            visited.append(node)
            current_level = levels[node]

            print(f"Level {current_level}: {node}")

            # explore children
            for child in graph[node]:
                if child not in visited and child not in queue:
                    queue.append(child)
                    levels[child] = current_level + 1

    # print BFS final order
    print("\n=== FINAL BFS ORDER ===")
    print(" → ".join(visited))

    # print levels grouped
    print("\n=== NODES GROUPED BY LEVEL ===")
    level_groups = {}
    for node, lvl in levels.items():
        level_groups.setdefault(lvl, []).append(node)

    for lvl in sorted(level_groups.keys()):
        print(f"Level {lvl}: {level_groups[lvl]}")


# run BFS
bfs_levels(graph, 'A')
