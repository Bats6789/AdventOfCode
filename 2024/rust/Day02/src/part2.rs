use std::{
    env,
    fs::File,
    io::{self, prelude::*, BufReader},
};

fn is_safe(left: Vec<i64>, right: Vec<i64>) -> bool {
    let mut climb: i64 = 0;

    for (l, r) in left.iter().zip(right.iter()) {
        if climb == 0 {
            climb = l - r;
        }

        if (l - r).abs() > 3 || (l - r).abs() < 1 {
            return false;
        }

        if climb < 0 && l > r {
            return false;
        } else if climb > 0 && l < r {
            return false;
        }
    }

    return true;
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

    let mut count: u64 = 0;

    for line in reader.lines() {
        let line = line?;
        let parts = line
            .split_whitespace()
            .map(|s| s.parse::<i64>().expect("Not a number"));
        let parts: Vec<i64> = parts.collect::<Vec<i64>>();

        let safe = is_safe((&parts[..parts.len() - 1]).to_vec(), (&parts[1..]).to_vec());

        if safe {
            count += 1;
            continue;
        }

        for i in 0..parts.len() {
            let mut sub_parts = parts.clone();
            sub_parts.remove(i);

            let safe = is_safe(
                (&sub_parts[..sub_parts.len() - 1]).to_vec(),
                (&sub_parts[1..]).to_vec(),
            );

            if safe {
                count += 1;
                break;
            }
        }
    }

    println!("{}", count);

    Ok(())
}
