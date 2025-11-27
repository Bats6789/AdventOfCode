use std::{
    env,
    fs::File,
    io::{self, prelude::*, BufReader},
};

use regex::Regex;

fn main() -> io::Result<()> {
    let args: Vec<_> = env::args().collect();

    let filename = if args.len() == 1 {
        "input.txt"
    } else {
        &args[1]
    };

    let file = File::open(filename)?;
    let mut reader = BufReader::new(file);

    let find_re = Regex::new(r"do\(\)|mul\(\d+,\d+\)|don't\(\)").unwrap();
    let unpack_re = Regex::new(r"mul\((?<val1>\d+),(?<val2>\d+)\)").unwrap();

    let mut total: i64 = 0;

    let mut str = String::new();
    let mut multiply = true;

    reader.read_to_string(&mut str).expect("Cannot read string");

    let caps: Vec<&str> = find_re.find_iter(&str).map(|m| m.as_str()).collect();

    for cap in caps.iter() {
        match cap {
            &"do()" => multiply = true,
            &"don't()" => multiply = false,
            _ => {
                if multiply {
                    let Some(vals) = unpack_re.captures(&cap) else {
                        return Ok(());
                    };
                    let val1 = &vals["val1"].parse::<i64>().unwrap();
                    let val2 = &vals["val2"].parse::<i64>().unwrap();
                    total += val1 * val2;
                }
            }
        }
    }

    println!("{}", total);

    Ok(())
}
