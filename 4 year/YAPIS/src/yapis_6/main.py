import numpy as np

def find_cycles(adj_matrix):
    n = len(adj_matrix)
    cycles = []

    def dfs(start, v, visited, path):
        for u in range(n):
            if adj_matrix[v][u]:
                if u == start and len(path) > 2:
                    cycle = path[:]
                    min_index = cycle.index(min(cycle))
                    cycle = cycle[min_index:] + cycle[:min_index]

                    rev = list(reversed(cycle))
                    min_index = rev.index(min(rev))
                    rev = rev[min_index:] + rev[:min_index]

                    norm_cycle = min(cycle, rev)

                    vec_cycle = np.array(norm_cycle, dtype=int)

                    if not any(np.array_equal(vec_cycle, c) for c in cycles):
                        cycles.append(vec_cycle)

                elif u not in visited:
                    dfs(start, u, visited | {u}, path + [u])

    for i in range(n):
        dfs(i, i, {i}, [i])
    return cycles


if __name__ == "__main__":
    adj = [
        [0, 1, 1, 0],
        [1, 0, 1, 1],
        [1, 1, 0, 1],
        [0, 1, 1, 0]
    ]

    result = find_cycles(adj)
    print("Найденные простые циклы (вектора):")
    for cycle in result:
        print(cycle)
