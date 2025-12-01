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

    let mut count: u32 = 0;
    let mut number: i32 = 50;

    for line_result in reader.lines() {
        let line = line_result.expect("Failed to extract line");
        let mut chars = line.chars();
        let c = chars.next().expect("Failed to parse char");
        let num: i32 = chars.collect::<String>().parse::<i32>().expect("Failed to parse integer") % 100;

		if c == 'L' {
			if num > number {
				number -= num;
				number += 100;
			} else {
				number -= num;
			}
		} else {
			number += num;
			number %= 100;
		}

		if number == 0 {
			count += 1;
		}
    }

    println!("{}", count);

    Ok(())
}
