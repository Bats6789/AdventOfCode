import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()
    lines = data.split('\n')

    beams = set()

    beams.add(lines[0].find('S'))

    count = 0

    for line in lines[1:]:
        new_beams = set()
        for beam in beams:
            if 0 <= beam < len(line) and line[beam] == '^':
                count += 1
                new_beams.add(beam - 1)
                new_beams.add(beam + 1)
            else:
                new_beams.add(beam)
        beams = new_beams

    print(count)

    return 0


if __name__ == '__main__':
    main()
