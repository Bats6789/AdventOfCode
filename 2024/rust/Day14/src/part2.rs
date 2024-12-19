use std::{
    env,
    fs::File,
    io::{self, prelude::*, BufReader},
    ops::AddAssign,
};

const HEIGHT: i64 = 103;
const WIDTH: i64 = 101;

#[derive(Clone, Copy, Debug)]
struct Point {
    x: i64,
    y: i64,
}

impl AddAssign for Point {
    fn add_assign(&mut self, rhs: Self) {
        self.x += rhs.x;
        self.y += rhs.y;
    }
}

#[derive(Debug)]
struct Robot {
    pos: Point,
    vel: Point,
}

impl Robot {
    fn travel(&mut self) {
        self.pos += self.vel;

        if self.pos.x < 0 {
            self.pos.x += WIDTH;
        }

        if self.pos.x >= WIDTH {
            self.pos.x -= WIDTH;
        }

        if self.pos.y < 0 {
            self.pos.y += HEIGHT;
        }

        if self.pos.y >= HEIGHT {
            self.pos.y -= HEIGHT;
        }
    }

    fn parse(str: String) -> Robot {
        let parts: Vec<String> = str.split(' ').map(|s| s.to_string()).collect();
        let pos_str = parts[0].split('=').last();
        let vel_str = parts[1].split('=').last();
        let pos_strs: Vec<String> = pos_str.unwrap().split(',').map(|s| s.to_string()).collect();
        let vel_strs: Vec<String> = vel_str.unwrap().split(',').map(|s| s.to_string()).collect();
        let pos = Point {
            x: pos_strs[0].parse().unwrap(),
            y: pos_strs[1].parse().unwrap(),
        };
        let vel = Point {
            x: vel_strs[0].parse().unwrap(),
            y: vel_strs[1].parse().unwrap(),
        };
        Robot { pos, vel }
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
    let reader = BufReader::new(file);

    let mut robots: Vec<Robot> = reader.lines().map(|l| Robot::parse(l.unwrap())).collect();
    let mut found_index = 0;
    let mut max_run = 0;
    let mut current_run = 0;
    let mut last_char;

    let mut grid: Vec<Vec<char>> = (0..HEIGHT).map(|_i| (0..WIDTH).map(|_i| ' ').collect()).collect();

    for i in 0..10000 {
        for row in grid.iter_mut() {
            for el in row.iter_mut() {
                *el = ' ';
            }
        }
        for robot in robots.iter_mut() {
            robot.travel();
            grid[robot.pos.y as usize][robot.pos.x as usize] = '#';
        }

        for row in grid.iter() {
            last_char = '\0';
            for &el in row {
                if el == '#' {
                    current_run += 1;
                } else if last_char == '#' {
                    if current_run > max_run {
                        max_run = current_run;
                        found_index = i + 1;
                    }
                    current_run = 0;
                }
                last_char = el;
            }
        }
    }


    println!("{}", found_index);

    Ok(())
}
