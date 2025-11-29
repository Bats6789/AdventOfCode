################################################
# File: Part1.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 1 for day 5 of AOC.               #
# Vers: 1.0.0 12/05/2023 CBW - Original code.  #
################################################
import sys


def applyMap(el, mapping):
    for dest, src, span in mapping:
        if src <= el < src + span:
            el = dest + (el - src)
            break
    return el


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    # Convert to blocks
    seeds, seedToSoil, soilToFert, fertToWater, \
        waterToLight, lightToTemp, tempToHum, humToLoc = data.split('\n\n')

    # Remove headers and split
    seeds = list(map(int, seeds.split(':')[1].strip().split()))
    seedToSoil = seedToSoil.split(':')[1].strip().split('\n')
    soilToFert = soilToFert.split(':')[1].strip().split('\n')
    fertToWater = fertToWater.split(':')[1].strip().split('\n')
    waterToLight = waterToLight.split(':')[1].strip().split('\n')
    lightToTemp = lightToTemp.split(':')[1].strip().split('\n')
    tempToHum = tempToHum.split(':')[1].strip().split('\n')
    humToLoc = humToLoc.split(':')[1].strip().split('\n')

    # split row on remaining list and covert to in
    seedToSoil = [list(map(int, s.strip().split())) for s in seedToSoil]
    soilToFert = [list(map(int, s.strip().split())) for s in soilToFert]
    fertToWater = [list(map(int, s.strip().split())) for s in fertToWater]
    waterToLight = [list(map(int, s.strip().split())) for s in waterToLight]
    lightToTemp = [list(map(int, s.strip().split())) for s in lightToTemp]
    tempToHum = [list(map(int, s.strip().split())) for s in tempToHum]
    humToLoc = [list(map(int, s.strip().split())) for s in humToLoc]

    minLoc = max([line[0] for line in humToLoc])
    for seed in seeds:
        soil = applyMap(seed, seedToSoil)
        fert = applyMap(soil, soilToFert)
        water = applyMap(fert, fertToWater)
        light = applyMap(water, waterToLight)
        temp = applyMap(light, lightToTemp)
        hum = applyMap(temp, tempToHum)
        loc = applyMap(hum, humToLoc)
        minLoc = min(minLoc, loc)

    print(minLoc)

    return 0


if __name__ == '__main__':
    main()
