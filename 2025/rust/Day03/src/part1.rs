use std::{
    env,
    fs::File,
    io::{self, prelude::*, BufReader},
};

use itertools::Itertools;

fn parse(line: String) -> i64 {
    let mut max = 0;

    for combination in line.chars().combinations(2) {
        let tmp: i64 = combination.into_iter().collect::<String>().parse().expect("Failed to parse string");
        max = if tmp > max {
            tmp
        } else {
            max
        };
    }

    return max;
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

    for line in reader.lines() {
        total += parse(line.expect("Failed to collect line"));
    }

    println!("{}", total);

    Ok(())
}
