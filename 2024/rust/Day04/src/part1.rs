use std::{
    env,
    fs::File,
    io::{self, prelude::*, BufReader},
};

fn main() -> io::Result<()> {
    let args: Vec<_> = env::args().collect();

    let filename = if args.len() == 1 {
        "input.txt"
    } else {
        &args[1]
    };

    let file = File::open(filename)?;
    let reader = BufReader::new(file);

    let mut count = 0;

    let grid: Vec<Vec<char>> = reader
        .lines()
        .map(|l| l.unwrap().chars().collect())
        .collect();

    for (i, line) in grid.iter().enumerate() {
        for (j, c) in line.iter().enumerate() {
            if *c == 'X' {
                // left
                if j > 2 {
                    if grid[i][j-3..j+1] == ['S', 'A', 'M', 'X'] {
                        count += 1;
                    }
                }
                // right
                if j < grid[0].len() - 3 {
                    if grid[i][j..j+4] == ['X', 'M', 'A', 'S'] {
                        count += 1;
                    }
                }
                // up
                if i > 2 {
                    if grid[i][j] == 'X'
                        && grid[i - 1][j] == 'M'
                        && grid[i - 2][j] == 'A'
                        && grid[i - 3][j] == 'S'
                    {
                        count += 1;
                    }
                }
                // down
                if i < grid.len() - 3 {
                    if grid[i][j] == 'X'
                        && grid[i + 1][j] == 'M'
                        && grid[i + 2][j] == 'A'
                        && grid[i + 3][j] == 'S'
                    {
                        count += 1;
                    }
                }
                // up-left
                if i > 2 && j > 2 {
                    if grid[i][j] == 'X'
                        && grid[i - 1][j - 1] == 'M'
                        && grid[i - 2][j - 2] == 'A'
                        && grid[i - 3][j - 3] == 'S'
                    {
                        count += 1;
                    }
                }
                // up-right
                if i > 2 && j < grid[0].len() - 3 {
                    if grid[i][j] == 'X'
                        && grid[i - 1][j + 1] == 'M'
                        && grid[i - 2][j + 2] == 'A'
                        && grid[i - 3][j + 3] == 'S'
                    {
                        count += 1;
                    }
                }
                // down-left
                if i < grid.len() - 3 && j > 2 {
                    if grid[i][j] == 'X'
                        && grid[i + 1][j - 1] == 'M'
                        && grid[i + 2][j - 2] == 'A'
                        && grid[i + 3][j - 3] == 'S'
                    {
                        count += 1;
                    }
                }
                // down-right
                if i < grid.len() - 3 && j < grid[0].len() - 3 {
                    if grid[i][j] == 'X'
                        && grid[i + 1][j + 1] == 'M'
                        && grid[i + 2][j + 2] == 'A'
                        && grid[i + 3][j + 3] == 'S'
                    {
                        count += 1;
                    }
                }
            }
        }
    }

    println!("{}", count);

    Ok(())
}
