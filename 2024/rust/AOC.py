#################################################
# Name: AOC.py                                  #
# Auth: Blake Wingard - bats23456789@gmail.com  #
# Desc: Setup specified day for Advent of Code. #
# Vers: 1.0.0 12/01/2023 CBW - Original Code.   #
#################################################
import argparse
import subprocess
import sys
from os import path
from os import mkdir
from os import system
from shutil import copyfile


def main():
    # Parser setup
    parser = argparse.ArgumentParser(prog='AOC',
                                     description='Setup Advent of code project',
                                     epilog='Blake Wingard - bats23456789@gmail.com')
    parser.add_argument('-s', '--session', type=str, required=True, help='The file containing a Session ID')
    parser.add_argument('-d', '--day', type=int, default=1, help='The day to setup')
    parser.add_argument('-y', '--year', type=int, default=2024, help='The year to setup')
    args = parser.parse_args()

    # Session setup
    SESSION = open(args.session).read().strip()

    # Directory validation
    dirName = f'Day{args.day:02d}'
    if path.isdir(dirName):
        return 0

    # Start collection input
    cmd = f'curl https://adventofcode.com/{args.year}/day/{args.day}/input --cookie "session={SESSION}"'
    output = subprocess.check_output(cmd, shell=True)

    # Setup path and files
    # mkdir(dirName)
    system(f'cargo init {dirName}')
    dataFileName = path.join(dirName, 'input.txt')
    scriptFileName = path.join(dirName, path.join('src', 'main.rs'))
    copyfile('template.rs', scriptFileName)

    output = output.decode('utf-8')
    dataFile = open(dataFileName, 'w')
    print(output, end='', file=dataFile)
    print('\n'.join(output.split('\n')[:10]), file=sys.stderr)

    return 0


if __name__ == '__main__':
    main()
