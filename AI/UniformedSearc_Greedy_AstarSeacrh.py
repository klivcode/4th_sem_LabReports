'''
Lab  3: Informed search (Greedy and A* Algorithm)

Objective: 
- To implement Greedy best first search and A* search to find optimal solution or near optimal solution using heuristics. 
'''

import heapq


class Graph:
    def __init__(self):
        self.graph = {}
        self.heuristics = {}

    def add_edge(self, u, v, cost):
        self.graph.setdefault(u, []).append((v, cost))
        self.graph.setdefault(v, []).append((u, cost))  # undirected

    def set_heuristics(self, h):
        self.heuristics = h

    # Greedy best first search
    def greedy_best_first_search(self, start, goal):
        visited = set()
        pq = [(self.heuristics[start], start)]  # assigning (h(n),value ) value
        path = []

        while pq:
            _, node = heapq.heappop(pq)

            if node is visited:
                continue
            visited.add(node)
            path.append(node)

            if node == goal:
                return path

            for neighbour, _ in self.graph.get(node, []):
                if neighbour not in visited:
                    heapq.heappush(pq, (self.heuristics[neighbour], neighbour))
        return None

    def a_star(self, start, goal):
        pq = [(self.heuristics[start], 0, start, [])]  # (f,g,node,path)

        visited = set()

        while pq:
            f, g, node, path = heapq.heappop(pq)

            if node is visited:
                continue
            visited.add(node)
            path = path + [node]

            if node == goal:
                return path, g  # return path and total cost

            for neighbour, cost in self.graph.get(node, []):
                if neighbour not in visited:
                    g_new = g + cost
                    f_new = g_new + self.heuristics[neighbour]
                    heapq.heappush(pq, (f_new, g_new, neighbour, path))
        return None, float('inf')

    # Example


if __name__ == "__main__":
    g = Graph()

    # graph connection

    g.add_edge('A', 'B', 1)
    g.add_edge('A', 'C', 3)
    g.add_edge('B', 'D', 3)
    g.add_edge('C', 'D', 1)
    g.add_edge('C', 'E', 5)
    g.add_edge('D', 'E', 2)

    # setting heuristics value
    h = {
        'A': 7,
        'B': 6,
        'C': 2,
        'D': 1,
        'E': 0
    }

    g.set_heuristics(h)

    # run greedy best first search

    print("Greedy Best first search: \n")
    path_gbfs = g.greedy_best_first_search('A', 'E')
    print("Path:", "->".join(path_gbfs))

    # run A* search
    print("\n Search path:")
    path_astar, cost = g.a_star('A', 'E')
    print("Path:", "->".join(path_astar))

    print("Cost:", cost)


