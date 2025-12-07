use std::{
    env,
    fs::File,
    io::{self, prelude::*, BufReader},
};

fn adjacent(grid: &Vec<Vec<char>>, row: usize, col: usize) -> i64 {
    let mut count = 0;

    if row > 0 {
        if col > 0 && grid[row - 1][col - 1] == '@' {
            count += 1;
        }
        if grid[row - 1][col] == '@' {
            count += 1;
        }
        if col < grid[0].len() - 1 && grid[row - 1][col + 1] == '@' {
            count += 1;
        }
    }

    if col > 0 && grid[row][col - 1] == '@' {
        count += 1;
    }
    if col < grid[0].len() - 1 && grid[row][col + 1] == '@' {
        count += 1;
    }

    if row < grid.len() - 1 {
        if col > 0 && grid[row + 1][col - 1] == '@' {
            count += 1;
        }
        if grid[row + 1][col] == '@' {
            count += 1;
        }
        if col < grid[0].len() - 1 && grid[row + 1][col + 1] == '@' {
            count += 1;
        }
    }

    return count;
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

    let grid: Vec<Vec<char>> = reader.lines()
        .filter_map(|line| line.ok())
        .map(|line| line.chars().collect())
        .collect();

    let width = grid[0].len();
    let height = grid.len();

    let mut count = 0;

    for row in 0..height {
        for col in 0..width {
            if grid[row][col] == '@' && adjacent(&grid, row, col) < 4 {
                count += 1;
            }
        }
    }

    println!("{}", count);

    Ok(())
}
