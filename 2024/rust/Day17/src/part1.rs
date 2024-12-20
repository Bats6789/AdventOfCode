use std::{
    env, fs::File, io::{self, prelude::*, BufReader}
};

fn get_combo(val: u64, a: u64, b: u64, c: u64) -> u64 {
    match val {
        4 => a,
        5 => b,
        6 => c,
        _ => val,
    }
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
    let mut lines = reader.lines();

    let mut a: u64 = lines
        .next()
        .unwrap()?
        .split(": ")
        .last()
        .unwrap()
        .parse()
        .unwrap();
    let mut b: u64 = lines
        .next()
        .unwrap()?
        .split(": ")
        .last()
        .unwrap()
        .parse()
        .unwrap();
    let mut c: u64 = lines
        .next()
        .unwrap()?
        .split(": ")
        .last()
        .unwrap()
        .parse()
        .unwrap();

    lines.next();

    let program: Vec<u64> = lines
        .next()
        .unwrap()
        .ok()
        .unwrap()
        .split(": ")
        .last()
        .unwrap()
        .split(',')
        .map(|el| el.parse().unwrap())
        .collect();

    let mut i: u64 = 0;

    let mut out: Vec<u64> = vec![];

    while (i as usize) < program.len() {
        let op = program[i as usize];
        i += 1;
        let val = program[i as usize] as u64;
        i += 1;

        match op {
            0 => {
                a = a >> get_combo(val, a, b, c);
            }
            1 => {
                b ^= val;
            }
            2 => {
                b = get_combo(val, a, b, c) % 8;
            }
            3 => {
                if a != 0 {
                    i = val;
                }
            }
            4 => {
                b ^= c;
            }
            5 => {
                out.push(get_combo(val, a, b, c) % 8);
            }
            6 => {
                b = a >> get_combo(val, a, b, c);
            }
            7 => {
                c = a >> get_combo(val, a, b, c);
            }
            _ => {
                panic!("All ops are not handled");
            }
        }
    }

    for (i, val) in out.iter().enumerate() {
        print!("{}", val);
        if i + 1 == out.len() {
            println!();
        } else {
            print!(",");
        }
    }

    Ok(())
}
