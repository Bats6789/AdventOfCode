use std::{
    collections::{HashMap, HashSet},
    env,
    fs::File,
    io::{self, prelude::*, BufReader},
    ops::{Add, Neg, Sub},
};

use itertools::Itertools;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Point {
    x: i64,
    y: i64,
}

impl Add for Point {
    type Output = Point;
    fn add(self, rhs: Point) -> Point {
        Point {
            x: self.x + rhs.x,
            y: self.y + rhs.y,
        }
    }
}

impl Sub for Point {
    type Output = Point;
    fn sub(self, rhs: Point) -> Point {
        Point {
            x: self.x - rhs.x,
            y: self.y - rhs.y,
        }
    }
}

impl Neg for Point {
    type Output = Point;
    fn neg(self) -> Point {
        Point {
            x: -self.x,
            y: -self.y,
        }
    }
}

fn inside(pt: Point, d: Point, max: Point) -> bool {
    let shift = pt + d;
    return 0 <= shift.x && shift.x < max.x && 0 <= shift.y && shift.y < max.y;
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

    let grid: Vec<Vec<char>> = reader
        .lines()
        .map(|l| l.unwrap().chars().collect())
        .collect();
    let mut unique_pts: Vec<char> = Vec::new();
    let mut points: HashMap<char, Vec<Point>> = HashMap::new();
    let mut seen: HashSet<Point> = HashSet::new();
    let mut count = 0;
    let max: Point = Point {
        x: grid[0].len() as i64,
        y: grid.len() as i64,
    };

    for (i, row) in grid.iter().enumerate() {
        for (j, el) in row.iter().enumerate() {
            if *el != '.' {
                if !unique_pts.contains(el) {
                    unique_pts.push(*el);
                }

                if !points.contains_key(el) {
                    points.insert(*el, Vec::new());
                }

                points.get_mut(el).unwrap().push(Point {
                    x: j as i64,
                    y: i as i64,
                });
            }
        }
    }

    for point in unique_pts {
        for mut it in points.get(&point).unwrap().iter().combinations(2) {
            let left: Point = *it.pop().unwrap();
            let right: Point = *it.pop().unwrap();

            let d = right - left;

            let shift = left - d;
            if inside(left, -d, max) && grid[shift.y as usize][shift.x as usize] != point {
                if !seen.contains(&shift) {
                    seen.insert(shift);
                    count += 1;
                }
            }

            let shift = right + d;
            if inside(right, d, max) && grid[shift.y as usize][shift.x as usize] != point {
                let shift = right + d;
                if !seen.contains(&shift) {
                    seen.insert(shift);
                    count += 1;
                }
            }
        }
    }

    println!("{}", count);

    Ok(())
}
