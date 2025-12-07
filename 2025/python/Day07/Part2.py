import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()
    lines = data.split('\n')

    beams = dict()

    beams[lines[0].find('S')] = 1

    for line in lines[1:]:
        new_beams = dict()
        for beam, count in beams.items():
            if 0 <= beam < len(line) and line[beam] == '^':
                if beam - 1 in new_beams:
                    new_beams[beam - 1] += count
                else:
                    new_beams[beam - 1] = count
                if beam + 1 in new_beams:
                    new_beams[beam + 1] += count
                else:
                    new_beams[beam + 1] = count
            else:
                if beam in new_beams:
                    new_beams[beam] += count
                else:
                    new_beams[beam] = count

        beams = new_beams

    print(sum(beams.values()))

    return 0


if __name__ == '__main__':
    main()
