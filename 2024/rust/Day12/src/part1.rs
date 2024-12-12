use std::{
    env,
    fs::File,
    io::{self, prelude::*, BufReader}, ops::AddAssign,
};

#[derive(Debug)]
struct Parameters {
    area: i64,
    perm: i64
}

impl AddAssign for Parameters {
    fn add_assign(&mut self, rhs: Self) {
        self.area += rhs.area;
        self.perm += rhs.perm;

        ()
    }
}

fn region(grid: &Vec<Vec<char>>, x: usize, y: usize, el: char, seen: &mut Vec<Vec<bool>>) -> Parameters {
    let mut res: Parameters = Parameters {area: 1, perm: 0};

    seen[y][x] = true;

    if x > 0 && grid[y][x - 1] == el && !seen[y][x - 1] {
        let walk_res = region(grid, x - 1, y, el, seen);
        res += walk_res;
    } else if x == 0 || grid[y][x - 1] != el {
        res.perm += 1;
    }

    if y > 0 && grid[y - 1][x] == el && !seen[y - 1][x] {
        let walk_res = region(grid, x, y - 1, el, seen);
        res += walk_res;
    } else if y == 0 || grid[y - 1][x] != el {
        res.perm += 1;
    }

    if x < grid[0].len() - 1 && grid[y][x + 1] == el && !seen[y][x + 1] {
        let walk_res = region(grid, x + 1, y, el, seen);
        res += walk_res;
    } else if x == grid[0].len() - 1 || grid[y][x + 1] != el {
        res.perm += 1;
    }

    if y < grid.len() - 1 && grid[y + 1][x] == el && !seen[y + 1][x] {
        let walk_res = region(grid, x, y + 1, el, seen);
        res += walk_res;
    } else if y == grid.len() - 1 || grid[y + 1][x] != el {
        res.perm += 1;
    }

    return res;
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

    let grid: Vec<Vec<char>> = reader.lines().map(|l| l.unwrap().chars().collect()).collect();
    let mut seen: Vec<Vec<bool>> = grid.iter().map(|l| l.iter().map(|_| false).collect()).collect();

    for (i, row) in grid.iter().enumerate() {
        for (j, el) in row.iter().enumerate() {
            if !seen[i][j] {
                let res = region(&grid, j, i, *el, &mut seen);
                total += res.area * res.perm;
            }
        }
    }

    println!("{}", total);

    Ok(())
}
