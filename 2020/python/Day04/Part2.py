import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    passports = data.split('\n\n')

    validPassport = 0

    for passport in passports:
        passport = passport.replace('\n', ' ')

        seenByr = False
        seenIyr = False
        seenEyr = False
        seenHgt = False
        seenHcl = False
        seenEcl = False
        seenPid = False

        for field in passport.split(' '):
            key, val = field.split(':')
            if key == 'byr':
                val = int(val)
                seenByr = 1920 <= val <= 2002
            elif key == 'iyr':
                val = int(val)
                seenIyr = 2010 <= val <= 2020
            elif key == 'eyr':
                val = int(val)
                seenEyr = 2020 <= val <= 2030
            elif key == 'hgt':
                if 'cm' in val:
                    val = int(val[:-2])
                    seenHgt = 150 <= val <= 193
                elif 'in' in val:
                    val = int(val[:-2])
                    seenHgt = 59 <= val <= 76
            elif key == 'hcl':
                if len(val) == 7 and val[0] == '#':
                    seenHcl = True
                    for c in val[1:]:
                        if not ('0' <= c <= '9' or 'a' <= c <= 'f'):
                            seenHcl = False
            elif key == 'ecl':
                seenEcl = val in ['amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth']
            elif key == 'pid':
                seenPid = len(val) == 9 and val.isdecimal()

        if all([seenByr, seenIyr, seenEyr, seenHgt, seenHcl, seenEcl, seenPid]):
            validPassport += 1

    print(validPassport)
    return 0


if __name__ == '__main__':
    main()
