use std::{
    collections::HashSet, env, fs::File, io::{self, prelude::*, BufReader}
};

#[derive(Debug)]
#[derive(Clone)]
#[derive(Copy)]
#[derive(Eq)]
#[derive(PartialEq)]
#[derive(Hash)]
enum Direction {
    Up,
    Down,
    Left,
    Right,
}

#[derive(Debug)]
#[derive(Eq, Hash, PartialEq)]
struct State {
    x: i64,
    y: i64,
    dir: Direction
}

fn inside(x: i64, y: i64, w: i64, h: i64) -> bool {
    return 0 < x && x < w - 1 && 0 < y && y < h - 1;
}

fn walk(startx: i64, starty: i64, grid: &Vec<Vec<char>>) -> bool {
    let mut dir: Direction = Direction::Up;
    let mut x = startx;
    let mut y = starty;

    let mut seen: HashSet<State> = HashSet::new();

    while inside(
        x,
        y,
        grid[0].len().try_into().unwrap(),
        grid.len().try_into().unwrap(),
    ) {
        let state: State = State {x, y, dir};
        match dir {
            Direction::Up => {
                if grid[(y - 1) as usize][x as usize] != '#' {
                    y -= 1;
                } else {
                    if seen.contains(&state) {
                        return true;
                    } else {
                        seen.insert(state);
                        dir = Direction::Right;
                    }
                }
            },
            Direction::Down => {
                if grid[(y + 1) as usize][x as usize] != '#' {
                    y += 1;
                } else {
                    if seen.contains(&state) {
                        return true;
                    } else {
                        seen.insert(state);
                        dir = Direction::Left;
                    }
                }
            },
            Direction::Left => {
                if grid[y as usize][(x - 1) as usize] != '#' {
                    x -= 1;
                } else {
                    if seen.contains(&state) {
                        return true;
                    } else {
                        seen.insert(state);
                        dir = Direction::Up;
                    }
                }
            },
            Direction::Right => {
                if grid[y as usize][(x + 1) as usize] != '#' {
                    x += 1;
                } else {
                    if seen.contains(&state) {
                        return true;
                    } else {
                        seen.insert(state);
                        dir = Direction::Down;
                    }
                }
            },
        }
    }

    return false;
}

fn main() -> io::Result<()> {
    let args: Vec<_> = env::args().collect();

    let filename = if args.len() == 1 {
        "input.txt"
    } else {
        &args[1]
    };

    let file = File::open(filename)?;
    let reader = BufReader::new(file);

    let mut grid: Vec<Vec<char>> = reader
        .lines()
        .map(|l| l.unwrap().chars().collect())
        .collect();

    let mut x: i64 = 0;
    let mut y: i64 = 0;
    let mut count: usize = 0;
    let mut dir: Direction = Direction::Up;

    for (i, row) in grid.iter().enumerate() {
        for (j, c) in row.iter().enumerate() {
            if *c == '^' {
                x = j.try_into().unwrap();
                y = i.try_into().unwrap();
                break;
            }
        }
    }

    let startx = x;
    let starty = y;

    while inside(
        x,
        y,
        grid[0].len().try_into().unwrap(),
        grid.len().try_into().unwrap(),
    ) {
        {
            let y = y as usize;
            let x = x as usize;
            if grid[y][x] != 'X' {
                grid[y][x] = 'X';
            }
        }

        match dir {
            Direction::Up => {
                if grid[(y - 1) as usize][x as usize] != '#' {
                    y -= 1;
                } else {
                    dir = Direction::Right;
                }
            },
            Direction::Down => {
                if grid[(y + 1) as usize][x as usize] != '#' {
                    y += 1;
                } else {
                    dir = Direction::Left;
                }
            },
            Direction::Left => {
                if grid[y as usize][(x - 1) as usize] != '#' {
                    x -= 1;
                } else {
                    dir = Direction::Up;
                }
            },
            Direction::Right => {
                if grid[y as usize][(x + 1) as usize] != '#' {
                    x += 1;
                } else {
                    dir = Direction::Down;
                }
            },
        }
    }

    for (i, row) in grid.clone().iter().enumerate() {
        for (j, c) in row.iter().enumerate() {
            if *c != '#' {
                grid[i][j] = '#';
                if walk(startx, starty, &grid) {
                    count += 1;
                }
                grid[i][j] = 'X';
            }
        }
    }

    println!("{}", count);

    Ok(())
}
