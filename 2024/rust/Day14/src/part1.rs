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

    for _ in 0..100 {
        for robot in robots.iter_mut() {
            robot.travel();
        }
    }

    let mut tl = 0;
    let mut tr = 0;
    let mut bl = 0;
    let mut br = 0;

    for robot in robots {
        let pos = robot.pos;
        if pos.x < WIDTH / 2 && pos.y < HEIGHT / 2 {
            tl += 1;
        }
        if pos.x < WIDTH / 2 && pos.y > HEIGHT / 2 {
            bl += 1;
        }
        if pos.x > WIDTH / 2 && pos.y < HEIGHT / 2 {
            tr += 1;
        }
        if pos.x > WIDTH / 2 && pos.y > HEIGHT / 2 {
            br += 1;
        }
    }

    println!("{}", tl * bl * tr * br);

    Ok(())
}
