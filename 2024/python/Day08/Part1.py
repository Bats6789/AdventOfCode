import sys
import itertools
import numpy as np


def inside(point, change, bounds):
    return np.all(bounds > point + change) and np.all(point + change >= 0)


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    count = 0

    # Convert data to grid
    grid = np.array(list(list(line) for line in data.split('\n')))

    # Grab boundaries
    bounds = grid.shape[::-1]

    # Acquire unique elements in grid that aren't '.'
    unique_els = np.unique(grid.flatten())
    unique_els = np.delete(unique_els, np.where(unique_els == '.'))

    # Collect every point of each unique element
    points_list = {el: list(zip(*np.where(grid == el))) for el in unique_els}

    # Process every set of points
    for points in points_list.values():
        for left, right in itertools.combinations(points, 2):
            change = np.subtract(right, left)

            if inside(left, -change, bounds):
                left = np.add(left, -change)
                if grid[*left] != '#':
                    grid[*left] = '#'
                    count += 1

            if inside(right, change, bounds):
                right = np.add(right, change)
                if grid[*right] != '#':
                    grid[*right] = '#'
                    count += 1

    print(count)

    return 0


if __name__ == '__main__':
    main()
