use std::{
    cmp::Reverse,
    collections::HashSet,
    env,
    fmt::{Display, Formatter, Result},
    fs::File,
    io::{self, prelude::*, BufReader},
};

use priority_queue::PriorityQueue;

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
struct Point {
    x: i64,
    y: i64,
}

impl Point {
    fn parse(str: &str) -> Point {
        let mut parts = str.split(',');

        let x = parts.next().unwrap().parse().unwrap();
        let y = parts.next().unwrap().parse().unwrap();

        Point { x, y }
    }
}

impl Display for Point {
    fn fmt(&self, f: &mut Formatter<'_>) -> Result {
        write!(f, "{},{}", self.x, self.y)
    }
}

fn can_solve(grid: &Vec<Vec<char>>) -> bool {
    let mut pq = PriorityQueue::new();

    let mut loc = Point { x: 0, y: 0 };
    let end = Point { x: 70, y: 70 };

    let mut seen: HashSet<Point> = HashSet::new();
    let mut step = 0;

    pq.push(loc, Reverse(step));

    while !pq.is_empty() && loc != end {
        let node = pq.pop().unwrap();
        loc = node.0;
        Reverse(step) = node.1;

        seen.insert(loc);

        if loc == end {
            break;
        }

        let tmp = Point {
            x: loc.x - 1,
            y: loc.y,
        };
        if loc.x > 0 && grid[tmp.y as usize][tmp.x as usize] != '#' && !seen.contains(&tmp) {
            pq.push(tmp, Reverse(step + 1));
        }

        let tmp = Point {
            x: loc.x + 1,
            y: loc.y,
        };
        if loc.x < (grid[0].len() as i64) - 1
            && grid[tmp.y as usize][tmp.x as usize] != '#'
            && !seen.contains(&tmp)
        {
            pq.push(tmp, Reverse(step + 1));
        }

        let tmp = Point {
            x: loc.x,
            y: loc.y - 1,
        };
        if loc.y > 0 && grid[tmp.y as usize][tmp.x as usize] != '#' && !seen.contains(&tmp) {
            pq.push(tmp, Reverse(step + 1));
        }

        let tmp = Point {
            x: loc.x,
            y: loc.y + 1,
        };
        if loc.y < (grid.len() as i64) - 1
            && grid[tmp.y as usize][tmp.x as usize] != '#'
            && !seen.contains(&tmp)
        {
            pq.push(tmp, Reverse(step + 1));
        }
    }

    return loc == end;
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

    let pts: Vec<Point> = reader.lines().map(|l| Point::parse(&l.unwrap())).collect();

    let mut grid: Vec<Vec<char>> = vec![vec!['.'; 71]; 71];

    let mut found_pt = Point { x: 0, y: 0 };

    for (i, pt) in pts.iter().enumerate() {
        grid[pt.y as usize][pt.x as usize] = '#';

        if i < 1024 {
            continue;
        }

        if !can_solve(&grid) {
            found_pt = *pt;
            break;
        }
    }

    println!("{}", found_pt);

    Ok(())
}
