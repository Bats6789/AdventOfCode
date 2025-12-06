import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    lines = data.split('\n')
    
    length = max(len(row) for row in lines)

    current_op = '+'
    vals = []
    total = 0

    for i in range(length + 1):
        if all(i >= len(row) or row[i] == ' ' for row in lines):
            if current_op == '*':
                tmp = 1
                for val in vals:
                    tmp *= val
                total += tmp
            else:
                total += sum(vals)
                
            vals = []
        else:
            if i < len(lines[-1]) and lines[-1][i] != ' ':
                current_op = lines[-1][i]
            
            vals.append(int(''.join([row[i] if i < len(row) else '' for row in lines[:-1]])))

    print(total)
    return 0


if __name__ == '__main__':
    main()
