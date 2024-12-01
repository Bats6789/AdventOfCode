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

    let mut left: Vec<u64> = vec![];
    let mut right: Vec<u64> = vec![];

    let mut dist: u64 = 0;

    for line in reader.lines() {
        let line = line?;
        let mut parts = line.split_whitespace().map(|s| s.parse::<u64>());

        match (parts.next(), parts.next()) {
            (Some(Ok(l)), Some(Ok(r))) => {
                left.push(l);
                right.push(r);
            }
            _ => {} // ignore invalid input
        }
    }

    left.sort();
    right.sort();

    for (l, r) in left.iter().zip(right.iter()) {
        dist += if l > r { l - r } else { r - l };
    }

    println!("{}", dist);

    Ok(())
}
