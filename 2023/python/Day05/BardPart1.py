def parse_map(map_data):
    """
    Parses the provided map data into a dictionary.

    Args:
    map_data: A string containing the map data.

    Returns:
    A dictionary mapping source values to destination values.
    """
    map_dict = {}
    for line in map_data.splitlines():
        if line:
            destination, source, range_length = map(int, line.split())
            for i in range(range_length):
                map_dict[source + i] = destination
    return map_dict


def convert_value(value, maps, target_map):
    """
    Converts a value through a series of maps until the target map is reached.

    Args:
    value: The initial value.
    maps: A dictionary containing all the maps.
    target_map: The name of the target map.

    Returns:
    The converted value.
    """
    current_value = value
    while True:
        # Check if a map exists for the current value
        map_name = f"{current_value}-to-"
        for map_type in maps.keys():
            if map_type.startswith(map_name):
                current_map = maps[map_type]
                break
            else:
                # No map found, stop conversion
                break

        # Apply the current map
        if current_value in current_map:
            current_value = current_map[current_value]
        else:
            # No mapping for this value, stop conversion
            break

        # Check if the target map has been reached
        if map_name == target_map:
            break

    return current_value


def solve(input_data):
    """
    Solves the challenge and returns the smallest location value.

    Args:
        input_data: A string containing the input data.

    Returns:
        The smallest location value for the seed values.
    """
    # Separate lines
    lines = input_data.strip().split("\n\n")

    # Parse data
    seeds = [int(s) for s in lines[0].split()[1:]]
    maps = {}
    for line in lines[1:]:
        map_type, map_data = line.split(':')
        maps[map_type] = parse_map(map_data)

    # Convert seeds and find smallest location
    lowest_location = min(convert_value(seed, maps, "humidity-to-location") for seed in seeds)

    return lowest_location


# Read the input data from a file
with open("example1.txt", "r") as f:
    input_data = f.read()

# Solve the challenge and print the result
print(solve(input_data))
