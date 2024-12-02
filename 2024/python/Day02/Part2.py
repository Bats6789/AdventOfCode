import sys


def is_safe(left, right):
    climb = 0
    for a, b in zip(left, right):
        if climb == 0:
            climb = int(a) - int(b)

        if not 3 >= abs(int(a) - int(b)) >= 1:
            return False

        if climb < 0 and int(a) > int(b):
            return False
        elif climb > 0 and int(a) < int(b):
            return False

    return True


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    count = 0
    for line in data.split('\n'):
        reports = line.split()

        safe = is_safe(reports[:-1], reports[1:])

        if safe:
            count += 1
            continue

        for i in range(len(reports)):
            sub_reports = list(reports)
            sub_reports.pop(i)
            safe = is_safe(sub_reports[:-1], sub_reports[1:])

            if safe:
                count += 1
                break

    print(count)
    return 0


if __name__ == '__main__':
    main()
