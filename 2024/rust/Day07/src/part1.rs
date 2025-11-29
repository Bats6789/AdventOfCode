use std::{
    env,
    fs::File,
    io::{self, prelude::*, BufReader},
};

fn valid(test: u64, values: &Vec<u64>) -> bool {
    if values.len() == 0 {
        return false;
    }

    if values.len() == 1 {
        return test == values[0];
    }

    let mut new_values: Vec<u64> = Vec::with_capacity(values.len() - 1);

    new_values.push(values[0] + values[1]);

    for value in values[2..].iter() {
        new_values.push(*value);
    }

    if valid(test, &new_values) {
        return true;
    }

    new_values[0] = values[0] * values[1];

    return valid(test, &new_values);
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
        let line = line.unwrap();
        let mut parts = line.split(": ");
        let test = parts.next().unwrap().parse::<u64>().unwrap();
        let values: Vec<u64> = parts
            .next()
            .unwrap()
            .split_whitespace()
            .map(|s| s.parse::<u64>().unwrap())
            .collect();

        if valid(test, &values) {
            total += test;
        }
    }

    println!("{}", total);

    Ok(())
}
