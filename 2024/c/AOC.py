#################################################
# Name: AOC.py                                  #
# Auth: Blake Wingard - bats23456789@gmail.com  #
# Desc: Setup specified day for Advent of Code. #
# Vers: 1.0.0 12/01/2023 CBW - Original Code.   #
#################################################
import argparse
import subprocess
import sys
from os import path, chdir, mkdir, system
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

    # Start collection input
    cmd = f'curl https://adventofcode.com/{args.year}/day/{args.day}/input --cookie "session={SESSION}"'
    output = subprocess.check_output(cmd, shell=True)

    # Setup path and files
    if not path.isdir(dirName):
        mkdir(dirName)
        part1FileName = path.join(dirName, 'Part1.c')
        part2FileName = path.join(dirName, 'Part2.c')
        buildFileName = path.join(dirName, 'CMakeLists.txt')
        copyfile('template.c', part1FileName)
        copyfile('template.c', part2FileName)
        copyfile('CMakeLists.txt.tmp', buildFileName)
        # Setup build
        buildDir = path.join(dirName, 'build')
        mkdir(buildDir)

        chdir(dirName)
        system('cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug -G"Unix Makefiles"')
        chdir('..')

    dataFileName = path.join(dirName, 'input.txt')
    output = output.decode('utf-8')
    dataFile = open(dataFileName, 'w')
    print(output, end='', file=dataFile)
    print('\n'.join(output.split('\n')[:10]), file=sys.stderr)

    return 0


if __name__ == '__main__':
    main()
