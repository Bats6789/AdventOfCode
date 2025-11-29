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
            if *c == 'A' {
                if grid[0].len() - 1 > i && i > 0 && grid.len() - 1 > j && j > 0 {
                    if (grid[i - 1][j - 1] == 'M' && grid[i][j] == 'A' && grid[i + 1][j + 1] == 'S'
                        || grid[i - 1][j - 1] == 'S'
                            && grid[i][j] == 'A'
                            && grid[i + 1][j + 1] == 'M')
                        && (grid[i + 1][j - 1] == 'M'
                            && grid[i][j] == 'A'
                            && grid[i - 1][j + 1] == 'S'
                            || grid[i + 1][j - 1] == 'S'
                                && grid[i][j] == 'A'
                                && grid[i - 1][j + 1] == 'M')
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
