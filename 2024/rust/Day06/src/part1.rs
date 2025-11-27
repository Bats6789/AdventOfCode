use std::{
    env,
    fs::File,
    io::{self, prelude::*, BufReader},
};

#[derive(Debug)]
enum Direction {
    Up,
    Down,
    Left,
    Right,
}

fn inside(x: i64, y: i64, w: i64, h: i64) -> bool {
    return 0 < x && x < w - 1 && 0 < y && y < h - 1;
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
    let mut count: usize = 1;
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
                count += 1;
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

    println!("{}", count);

    Ok(())
}
