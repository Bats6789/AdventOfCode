use std::{
    collections::HashSet,
    env,
    fs::File,
    io::{self, prelude::*, BufReader},
};

fn walk(grid: &Vec<Vec<u32>>, x: usize, y: usize, el: u32, seen: &mut HashSet<(usize, usize)>) -> u64 {
    let mut total: u64 = 0;

    if el == 9 {
        if seen.contains(&(x, y)) {
            return 0;
        } else {
            seen.insert((x, y));
            return 1;
        }
    }

    if x > 0 && grid[y][x - 1] == el + 1 {
        total += walk(grid, x - 1, y, el + 1, seen);
    }
    if y > 0 && grid[y - 1][x] == el + 1 {
        total += walk(grid, x, y - 1, el + 1, seen);
    }
    if x < grid[0].len() - 1 && grid[y][x + 1] == el + 1 {
        total += walk(grid, x + 1, y, el + 1, seen);
    }
    if y < grid.len() - 1 && grid[y + 1][x] == el + 1 {
        total += walk(grid, x, y + 1, el + 1, seen);
    }

    return total;
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
    let mut total = 0;

    let grid: Vec<Vec<u32>> = reader
        .lines()
        .map(|l| {
            l.unwrap()
                .chars()
                .map(|c| c.to_digit(10).unwrap())
                .collect()
        })
        .collect();

    for (i, row) in grid.iter().enumerate() {
        for (j, el) in row.iter().enumerate() {
            if *el == 0 {
                let mut seen: HashSet<(usize, usize)> = HashSet::new();
                total += walk(&grid, j, i, 0, &mut seen);
            }
        }
    }

    println!("{}", total);

    Ok(())
}
