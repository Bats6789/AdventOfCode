import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    count = 0
    for line in data.split('\n'):
        reports = line.splitc
        skip = False
        climb = 0
        for a, b in zip(reports[:-1], reports[1:]):
            if climb == 0:
                climb = int(a) - int(b)

            if not 3 >= abs(int(a) - int(b)) >= 1:
                skip = True
                break

            if climb < 0 and int(a) > int(b):
                skip = True
                break
            elif climb > 0 and int(a) < int(b):
                skip = True
                break

        if not skip:
            count += 1

    print(count)
    return 0


if __name__ == '__main__':
    main()
