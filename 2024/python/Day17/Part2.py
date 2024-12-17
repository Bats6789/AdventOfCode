import sys


def get_chunks(program, regA, regB, regC, checked_chunks):
    if checked_chunks == []:
        return regA, True

    chunk = int(checked_chunks[0])

    for i in range(8):
        tmp = (regA << 3) + i

        check = ((i ^ 4) ^ (tmp >> (i ^ 1))) % 8
        if check == chunk:
            val, res = get_chunks(program, tmp, regB, regC, checked_chunks[1:])
            if res:
                return val, True

    return regA, False


def get_combo(combo, regA, regB, regC):
    assert (combo != 7)
    match combo:
        case 0, 1, 2, 3:
            combo = combo
        case 4:
            combo = regA
        case 5:
            combo = regB
        case 6:
            combo = regC
    return combo


def run_prog(program, regA, regB, regC):
    iop = 0

    out = []
    while iop < len(program):
        op = int(program[iop])
        iop += 1
        combo = int(program[iop])
        iop += 1

        match op:
            case 0:
                combo = get_combo(combo, regA, regB, regC)
                regA = regA // 2**combo
            case 1:
                regB = regB ^ combo
            case 2:
                regB = get_combo(combo, regA, regB, regC) % 8
            case 3:
                if regA != 0:
                    iop = combo
            case 4:
                regB = regB ^ regC
            case 5:
                out.append(get_combo(combo, regA, regB, regC) % 8)
            case 6:
                combo = get_combo(combo, regA, regB, regC)
                regB = regA // 2**combo
            case 7:
                combo = get_combo(combo, regA, regB, regC)
                regC = regA // 2**combo
    return out


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    regA, regB, regC, _, program = data.split('\n')

    regA = int(regA.split(': ')[1])
    regB = int(regB.split(': ')[1])
    regC = int(regC.split(': ')[1])

    program = program.split(': ')[1]
    program = program.split(',')

    regA, res = get_chunks(program, 0, regB, regC, list(reversed(program)))

    print(regA)

    return 0


if __name__ == '__main__':
    main()
