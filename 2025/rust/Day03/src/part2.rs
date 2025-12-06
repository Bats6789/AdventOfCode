use std::{
    env,
    fs::File,
    io::{self, prelude::*, BufReader},
};

fn parse(line: String) -> i64 {
    let mut indexes: [usize; 12] = [0; 12];

    for i in 0..12 {
        indexes[i] = line.len() - 12 + i;
    }

    let line = line.into_bytes();

    for i in 0..12 {
        let start = if i == 0 {
            0
        } else {
            indexes[i - 1] + 1
        };
        let stop = indexes[i];

        for j in start..stop {
            if line[j] > line[indexes[i]] || (line[j] == line[indexes[i]] && j < indexes[i]) {
                indexes[i] = j;
            }
        }
    }

    let mut val: i64 = 0;

    for i in 0..12 {
        val *= 10;
        val += (line[indexes[i]] as char).to_digit(10).expect("Failed to convert char") as i64;
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
    let reader = BufReader::new(file);

    let mut total = 0;

    for line in reader.lines() {
        total += parse(line.expect("Failed to collect line"));
    }

    println!("{}", total);

    Ok(())
}
