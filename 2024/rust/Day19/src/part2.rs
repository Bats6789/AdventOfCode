use std::{
    env,
    fs::File,
    io::{self, prelude::*, BufReader},
};

use memoize::memoize;

#[memoize]
fn valid_pattern(towels: Vec<String>, desired: String) -> u64 {

    if desired.len() == 0 {
        return 1;
    }

    let mut val = 0;

    for towel in towels.iter() {
        let len = towel.len();

        if len > desired.len() {
            continue;
        }

        if *towel == desired[0..len] {
            val += valid_pattern(towels.clone(), desired[len..desired.len()].to_string());
        }
    }

    return val;
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

    let mut str: String = String::new();

    let _ = reader.read_to_string(&mut str);

    let mut parts = str.split("\r\n\r\n");

    let towels: Vec<String> = parts.next().unwrap().split(", ").map(|s| s.to_string()).collect();

    let patterns: Vec<String> = parts.next().unwrap().split("\r\n").map(|s| s.to_string()).filter(|s| !s.is_empty()).collect();

    let count: u64 = patterns.iter().map(|pat| valid_pattern(towels.clone(), pat.to_string())).sum();

    println!("{}", count);

    Ok(())
}
