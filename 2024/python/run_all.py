from os import chdir, path
import glob
import requests
import argparse
import subprocess


def main():
    # Parser setup
    parser = argparse.ArgumentParser(prog='run_all',
                                     description='Run all AOC solutions and log the output',
                                     epilog='Blake Wingard - bats23456789@gmail.com')

    parser.add_argument('-s', '--session', type=argparse.FileType('r'),
                        required=True, help='The file containing the Session ID')

    args = parser.parse_args()

    # Session setup
    cookies = {
        'session': args.session.read().strip()
    }

    # File for export
    output_file = open('output.txt', mode='w')

    # Gather all outputs
    dirs = glob.glob("Day*")

    for dir in dirs:
        input_file = path.join(dir, "input.txt")
        answer_file = path.join(dir, "answers.txt")

        # Download input if needed
        if not path.exists(input_file):
            day = int(dir[3:])
            print(f'Downloading input for Day {day}')

            url = f"https://adventofcode.com/2024/day/{day}/input"
            response = requests.get(url, cookies=cookies)

            with open(input_file, mode='w') as f:
                f.write(response.text)

        # Download answers if needed
        if not path.exists(answer_file):
            results = subprocess.run(['python', 'collect_ans.py',
                                      '-s', args.session.name,
                                      '-d', f'{dir[3:]}',
                                      '-o', answer_file],
                                     capture_output=True,
                                     text=True)

        # Run problems
        print(f'{dir}:', file=output_file)

        chdir(dir)

        # Collect answers
        with open('answers.txt', mode='r') as f:
            s = f.readline()
            part1_ans = s[8:].strip()
            s = f.readline()
            part2_ans = s[8:].strip()

        # Part 1
        print(f'{dir}: Part 1')

        results = subprocess.run(['python', 'Part1.py'], capture_output=True, text=True)
        answer = results.stdout.strip()

        if answer != part1_ans:
            print(f'Expected: {part1_ans}\nActual: {answer}')

        print(f'{answer}')
        print(f'Part 1: {answer}', file=output_file)

        # Part 2
        print(f'{dir}: Part 2')

        results = subprocess.run(['python', 'Part2.py'], capture_output=True, text=True)
        answer = results.stdout.strip()

        if answer != part2_ans:
            print(f'Expected: {part2_ans}\nActual: {answer}')

        print(f'{answer}')
        print(f'Part 2: {answer}', file=output_file)

        chdir('..')

    return 0


if __name__ == "__main__":
    main()
