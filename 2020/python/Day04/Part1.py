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
            key, _ = field.split(':')
            if key == 'byr':
                seenByr = True
            elif key == 'iyr':
                seenIyr = True
            elif key == 'eyr':
                seenEyr = True
            elif key == 'hgt':
                seenHgt = True
            elif key == 'hcl':
                seenHcl = True
            elif key == 'ecl':
                seenEcl = True
            elif key == 'pid':
                seenPid = True

        if all([seenByr, seenIyr, seenEyr, seenHgt, seenHcl, seenEcl, seenPid]):
            validPassport += 1

    print(validPassport)
    return 0


if __name__ == '__main__':
    main()
