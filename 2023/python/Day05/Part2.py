################################################
# File: Part2.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 2 for day 6 of AOC.               #
# Vers: 1.0.0 12/05/2023 CBW - Original code.  #
################################################
import sys


def applyMap(el, mapping):
    queue = [el]
    answers = []
    while queue != []:
        start, span = queue.pop(0)
        found = False
        for dest, src, mapSpan in mapping:
            if src <= start < src + mapSpan:
                if start + span <= src + mapSpan:
                    answers.append((dest + (start - src), span))
                else:
                    dist = (src + mapSpan) - start
                    answers.append((dest + (start - src), dist))
                    queue.append((start + dist, span - dist))
                found = True
                break
            elif start < src < start + span:
                if src + mapSpan < start + span:
                    queue.append((src + mapSpan, (start + span) - (src + mapSpan)))
                    answers.append((dest, mapSpan))
                    span = src - start
                else:
                    dist = (start + span) - src
                    answers.append((dest, dist))
                    span -= dist
        if not found:
            answers.append((start, span))

    if answers == []:
        answers = [el]

    return answers


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
    for seed in zip(seeds[0::2], seeds[1::2]):
        # Clear list
        ferts = []
        waters = []
        lights = []
        temps = []
        hums = []
        locs = []

        # map list
        soils = applyMap(seed, seedToSoil)
        for soil in soils:
            for el in applyMap(soil, soilToFert):
                ferts.append(el)
        for fert in ferts:
            for el in applyMap(fert, fertToWater):
                waters.append(el)
        for water in waters:
            for el in applyMap(water, waterToLight):
                lights.append(el)
        for light in lights:
            for el in applyMap(light, lightToTemp):
                temps.append(el)
        for temp in temps:
            for el in applyMap(temp, tempToHum):
                hums.append(el)
        for hum in hums:
            for el in applyMap(hum, humToLoc):
                locs.append(el)

        # Grab loc
        locs = [start for start, _ in locs]
        minLoc = min(minLoc, min(locs))

    print(minLoc)

    return 0


if __name__ == '__main__':
    main()
