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

    let lines: Vec<Vec<char>> = reader.lines().filter_map(|line| line.ok()).map(|line| line.chars().collect()).collect();
    let mut op: char = '+';

    let max_length = lines.iter().map(|line| line.len()).max().expect("Failed to get max length");
    let val_length = lines.len() - 1;
    let mut vals: Vec<i64> = vec![0; val_length];
    let mut val_index = 0;

    let mut total: i64 = 0;

    for i in 0..max_length {
        if lines.iter().all(|line| line[i] == ' ') {
            total += if op == '+' {
                vals.iter().take(val_index).sum::<i64>()
            } else {
                vals.iter().take(val_index).product()
            };

            for j in 0..val_index {
                vals[j] = 0;
            }
            val_index = 0;
        } else {
            if lines[val_length][i] != ' ' {
                op = lines[val_length][i];
            }

            for j in 0..val_length {
                if lines[j][i] != ' ' {
                    vals[val_index] *= 10;
                    vals[val_index] += lines[j][i].to_digit(10).expect("Failed to parse item") as i64;
                }
            }
            val_index += 1;
        }
    }
    total += if op == '+' {
        vals.iter().take(val_index).sum::<i64>()
    } else {
        vals.iter().take(val_index).product()
    };

    println!("{}", total);

    Ok(())
}
