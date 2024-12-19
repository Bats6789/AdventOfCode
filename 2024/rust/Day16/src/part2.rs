use std::{
    cmp::Reverse,
    collections::HashSet,
    env,
    fs::File,
    io::{self, prelude::*, BufReader},
    ops::{Add, AddAssign},
};

use priority_queue::PriorityQueue;

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
enum Direction {
    Up,
    Down,
    Left,
    Right,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
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

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
struct Step {
    pt: Point,
    dir: Direction,
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
        .map(|l| l.unwrap().chars().filter(|c| !c.is_whitespace()).collect())
        .collect();

    let mut start = Point { x: 0, y: 0 };
    let mut stop = Point { x: 0, y: 0 };

    for (i, row) in grid.iter().enumerate() {
        for (j, el) in row.iter().enumerate() {
            if *el == 'S' {
                start.x = j as i64;
                start.y = i as i64;
            }
            if *el == 'E' {
                stop.x = j as i64;
                stop.y = i as i64;
            }
        }
    }

    let mut pq = PriorityQueue::new();

    let step = Step {
        pt: start + Point { x: 1, y: 0 },
        dir: Direction::Right,
    };
    if grid[step.pt.y as usize][step.pt.x as usize] != '#' {
        pq.push(
            (step, vec![start, start + Point { x: 1, y: 0 }]),
            Reverse(1),
        );
    }

    let step = Step {
        pt: start,
        dir: Direction::Up,
    };
    pq.push((step, vec![start]), Reverse(1000));

    let mut score;
    let mut best_score = 1000000000;

    let mut seen: HashSet<Step> = HashSet::new();
    let mut valid: HashSet<Point> = HashSet::new();

    while !pq.is_empty() {
        let el = pq.pop().unwrap();

        let node = el.0;
        Reverse(score) = el.1;

        let step = node.0;
        let path = node.1;

        if step.pt == stop {
            best_score = best_score.min(score);

            if best_score == score {
                for item in path {
                    valid.insert(item);
                }
            }

            continue;
        }

        seen.insert(step);

        match step.dir {
            Direction::Up => {
                let check = step.pt + Point { x: 0, y: -1 };
                let mut new_path = path.clone();
                new_path.push(check);

                if !seen.contains(&Step {
                    pt: check,
                    dir: step.dir,
                }) && check.y > 0
                    && grid[check.y as usize][check.x as usize] != '#'
                {
                    pq.push(
                        (
                            Step {
                                pt: check,
                                dir: step.dir,
                            },
                            new_path,
                        ),
                        Reverse(score + 1),
                    );
                }

                if !seen.contains(&Step {
                    pt: step.pt,
                    dir: Direction::Left,
                }) {
                    pq.push(
                        (
                            Step {
                                pt: step.pt,
                                dir: Direction::Left,
                            },
                            path.clone(),
                        ),
                        Reverse(score + 1000),
                    );
                }

                if !seen.contains(&Step {
                    pt: step.pt,
                    dir: Direction::Right,
                }) {
                    pq.push(
                        (
                            Step {
                                pt: step.pt,
                                dir: Direction::Right,
                            },
                            path.clone(),
                        ),
                        Reverse(score + 1000),
                    );
                }
            }
            Direction::Down => {
                let check = step.pt + Point { x: 0, y: 1 };
                let mut new_path = path.clone();
                new_path.push(check);

                if !seen.contains(&Step {
                    pt: check,
                    dir: step.dir,
                }) && check.y < (grid.len() as i64)
                    && grid[check.y as usize][check.x as usize] != '#'
                {
                    pq.push(
                        (
                            Step {
                                pt: check,
                                dir: step.dir,
                            },
                            new_path,
                        ),
                        Reverse(score + 1),
                    );
                }

                if !seen.contains(&Step {
                    pt: step.pt,
                    dir: Direction::Left,
                }) {
                    pq.push(
                        (
                            Step {
                                pt: step.pt,
                                dir: Direction::Left,
                            },
                            path.clone(),
                        ),
                        Reverse(score + 1000),
                    );
                }

                if !seen.contains(&Step {
                    pt: step.pt,
                    dir: Direction::Right,
                }) {
                    pq.push(
                        (
                            Step {
                                pt: step.pt,
                                dir: Direction::Right,
                            },
                            path.clone(),
                        ),
                        Reverse(score + 1000),
                    );
                }
            }
            Direction::Left => {
                let check = step.pt + Point { x: -1, y: 0 };
                let mut new_path = path.clone();
                new_path.push(check);

                if !seen.contains(&Step {
                    pt: check,
                    dir: step.dir,
                }) && check.x > 0
                    && grid[check.y as usize][check.x as usize] != '#'
                {
                    pq.push(
                        (
                            Step {
                                pt: check,
                                dir: step.dir,
                            },
                            new_path,
                        ),
                        Reverse(score + 1),
                    );
                }

                if !seen.contains(&Step {
                    pt: step.pt,
                    dir: Direction::Up,
                }) {
                    pq.push(
                        (
                            Step {
                                pt: step.pt,
                                dir: Direction::Up,
                            },
                            path.clone(),
                        ),
                        Reverse(score + 1000),
                    );
                }

                if !seen.contains(&Step {
                    pt: step.pt,
                    dir: Direction::Down,
                }) {
                    pq.push(
                        (
                            Step {
                                pt: step.pt,
                                dir: Direction::Down,
                            },
                            path.clone(),
                        ),
                        Reverse(score + 1000),
                    );
                }
            }
            Direction::Right => {
                let check = step.pt + Point { x: 1, y: 0 };
                let mut new_path = path.clone();
                new_path.push(check);

                if !seen.contains(&Step {
                    pt: check,
                    dir: step.dir,
                }) && check.x < (grid[0].len() as i64)
                    && grid[check.y as usize][check.x as usize] != '#'
                {
                    pq.push(
                        (
                            Step {
                                pt: check,
                                dir: step.dir,
                            },
                            new_path,
                        ),
                        Reverse(score + 1),
                    );
                }

                if !seen.contains(&Step {
                    pt: step.pt,
                    dir: Direction::Up,
                }) {
                    pq.push(
                        (
                            Step {
                                pt: step.pt,
                                dir: Direction::Up,
                            },
                            path.clone(),
                        ),
                        Reverse(score + 1000),
                    );
                }

                if !seen.contains(&Step {
                    pt: step.pt,
                    dir: Direction::Down,
                }) {
                    pq.push(
                        (
                            Step {
                                pt: step.pt,
                                dir: Direction::Down,
                            },
                            path.clone(),
                        ),
                        Reverse(score + 1000),
                    );
                }
            }
        }
    }

    println!("{}", valid.len());

    Ok(())
}
