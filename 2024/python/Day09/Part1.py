import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    id = 0
    free = False

    format = list()

    for c in data:
        rep = ord(c) - ord('0')
        ch = chr(ord('0') + id)
        if free and rep != 0:
            format.append(['.', rep])
        elif rep != 0:
            format.append([ch, rep])

        id += 0 if free else 1

        free = not free

    quit = False
    shift = 0
    for i in range(len(format)):
        i += shift
        c, rep = format[i]
        if c == '.':
            for j in range(len(format)):
                j = len(format) - j - 1
                ch, rep2 = format[j]
                if j <= i:
                    quit = True
                    break
                if ch != '.' and rep2 > 0:
                    if rep2 >= rep:
                        rep2 -= rep
                        format[j] = [ch, rep2]
                        format[i] = [ch, rep]
                        break
                    else:
                        format.insert(i, [ch, rep2])
                        shift += 1
                        i += 1
                        j += 1
                        rep -= rep2
                        format[j] = [ch, 0]
            if quit:
                break

    total = 0
    scale = 0
    for [c, rep] in format:
        if c == '.':
            break

        val = ord(c) - ord('0')
        for i in range(rep):
            total += val * scale
            scale += 1

    print(total)

    return 0


if __name__ == '__main__':
    main()
