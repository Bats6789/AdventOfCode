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

    let mut lines: Vec<String> = reader.lines().filter_map(|line| line.ok()).collect();

    let ops_str: String = lines.pop().expect("Failed to pop element");
    let vals_str: Vec<String> = lines;

    let ops: Vec<char> = ops_str.chars().filter(|c| !c.is_whitespace()).collect();
    let vals: Vec<Vec<i64>> = vals_str.iter().map(|line| line.split_whitespace().filter_map(|chunk| chunk.parse().ok()).collect()).collect();

    let mut total: i64 = 0;

    for (i, op) in ops.iter().enumerate() {
        if *op == '+' {
            total += vals.iter().map(|row| row[i]).sum::<i64>();
        } else {
            total += vals.iter().map(|row| row[i]).product::<i64>();
        }
    }

    println!("{}", total);

    Ok(())
}
