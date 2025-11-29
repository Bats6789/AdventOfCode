use std::{
    env,
    fs::File,
    io::{self, prelude::*, BufReader},
    ops::{Add, AddAssign},
};

#[derive(Clone, Copy, Debug, PartialEq)]
struct Point {
    x: i64,
    y: i64,
}

impl Add for Point {
    type Output = Point;

    fn add(self, rhs: Self) -> Self::Output {
        Point {
            x: self.x + rhs.x,
            y: self.y + rhs.y,
        }
    }
}

impl AddAssign for Point {
    fn add_assign(&mut self, rhs: Self) {
        self.x += rhs.x;
        self.y += rhs.y;
    }
}

#[derive(Debug, PartialEq)]
struct Shift {
    to: Point,
    from: Point,
}

fn get_shifts(grid: &Vec<Vec<char>>, pos: Point, d: Point, shift_list: &mut Vec<Shift>) -> bool {
    if grid[pos.y as usize][pos.x as usize] == '.' {
        return true;
    } else if grid[pos.y as usize][pos.x as usize] == '#' {
        return false;
    } else if get_shifts(grid, pos + d, d, shift_list) {
        let shift = Shift {
            to: pos + d,
            from: pos,
        };
        if !shift_list.contains(&shift) {
            shift_list.push(shift);
        }
        return true;
    } else {
        return false;
    }
}

fn main() -> io::Result<()> {
    let args: Vec<_> = env::args().collect();

    let filename = if args.len() == 1 {
        "input.txt"
    } else {
        &args[1]
    };

    let file = File::open(filename)?;
    let mut reader = BufReader::new(file);

    let mut data: String = "".to_string();
    let _ = reader.read_to_string(&mut data);

    let mut parts = data.split("\r\n\r\n");
    let mut score = 0;

    let mut grid: Vec<Vec<char>> = parts
        .next()
        .unwrap()
        .split_whitespace()
        .map(|l| l.chars().collect())
        .collect();
    let path: Vec<char> = parts
        .next()
        .unwrap()
        .chars()
        .filter(|c| !c.is_whitespace())
        .collect();

    let mut pos = Point { x: 0, y: 0 };

    let mut shift_list: Vec<Shift> = vec![];

    for (i, row) in grid.iter().enumerate() {
        for (j, el) in row.iter().enumerate() {
            if *el == '@' {
                pos.x = j as i64;
                pos.y = i as i64;
            }
        }
    }

    for step in path {
        let d = match step {
            '^' => Point { x: 0, y: -1 },
            '<' => Point { x: -1, y: 0 },
            '>' => Point { x: 1, y: 0 },
            'v' => Point { x: 0, y: 1 },
            _ => Point { x: -100, y: -100 },
        };

        if get_shifts(&grid, pos.clone(), d.clone(), &mut shift_list) {
            for shift in shift_list.iter() {
                let to = shift.to;
                let from = shift.from;

                grid[to.y as usize][to.x as usize] = grid[from.y as usize][from.x as usize];
            }
            grid[pos.y as usize][pos.x as usize] = '.';
            pos += d;
            grid[pos.y as usize][pos.x as usize] = '@';
        }

        shift_list.clear();
    }

    for (i, row) in grid.iter().enumerate() {
        for (j, el) in row.iter().enumerate() {
            if *el == 'O' {
                score += 100 * i + j;
            }
        }
    }

    println!("{}", score);

    Ok(())
}
