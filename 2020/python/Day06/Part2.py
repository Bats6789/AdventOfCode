import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    count = 0

    for group in data.split('\n\n'):
        answers = dict()

        for person in group.split('\n'):
            for c in person:
                if c not in answers.keys():
                    answers[c] = 1
                else:
                    answers[c] += 1

        groupLen = len(group.split('\n'))
        for val in answers.values():
            if val == groupLen:
                count += 1

    print(count)

    return 0


if __name__ == '__main__':
    main()
