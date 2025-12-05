use std::{
    env,
    fs::File,
    io::{self, prelude::*, BufReader},
};

fn is_invalid(value: i64) -> bool {
    let value_str = value.to_string();
    let (left, right) = value_str.split_at(value_str.len() / 2);

    return left == right;
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
    let mut contents = String::new();
    let _ = reader.read_to_string(&mut contents);

    let mut total = 0;

    for range in contents.split(',') {
        if let Some((start_str, stop_str)) = range.split_once('-') {
            let start: i64 = start_str.trim().parse().expect(&format!("Failed to parse start: {}", start_str));
            let stop: i64 = stop_str.trim().parse().expect(&format!("Failed to parse stop: {}", stop_str));

            for i in start..=stop {
                if is_invalid(i) {
                    total += i;
                }
            }
        } else {
            println!("Failed to parse: {}", range);
        }
    }

    println!("{}", total);

    Ok(())
}
