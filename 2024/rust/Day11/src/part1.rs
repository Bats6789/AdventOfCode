use memoize::memoize;
use std::{
    env,
    fs::File,
    io::{self, prelude::*, BufReader},
};

#[memoize]
fn get_stones(value: u64, tick: u64) -> u64 {
    if tick == 0 {
        return 1;
    } else if value == 0 {
        return get_stones(1, tick - 1);
    } else if (value.ilog10() + 1) % 2 == 0 {
        let shift = 10_u64.pow((value.ilog10() + 1) / 2);
        let left = value / shift;
        let right = value % shift;
        return get_stones(left, tick - 1) + get_stones(right, tick - 1);
    } else {
        return get_stones(value * 2024, tick - 1);
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
    let mut reader = BufReader::new(file);
    let mut line: String = String::new();
    let _ = reader.read_line(&mut line);

    let total: u64 = line
        .split_whitespace()
        .map(|el| get_stones(el.parse().unwrap(), 25))
        .sum();

    println!("{}", total);

    Ok(())
}
