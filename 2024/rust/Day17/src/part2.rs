use std::{
    env, fs::File, io::{self, prelude::*, BufReader}
};

fn get_values(program: &Vec<i64>, a: i64, b: i64, c: i64) -> i64 {

    if program.len() == 0 {
        return a;
    }

    let mut new_program: Vec<i64> = program.clone();
    let chunk = new_program.pop().unwrap();

    for i in 0..8 {
        let tmp = (a << 3) + i;
        let check = ((i ^ 4) ^ (tmp >> (i ^ 1))) % 8;

        if check == chunk {
            let val = get_values(&new_program, tmp, b, c);

            if val >= 0 {
                return val;
            }
        }
    }

    return -1;
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

    let _: i64 = lines
        .next()
        .unwrap()?
        .split(": ")
        .last()
        .unwrap()
        .parse()
        .unwrap();
    let b: i64 = lines
        .next()
        .unwrap()?
        .split(": ")
        .last()
        .unwrap()
        .parse()
        .unwrap();
    let c: i64 = lines
        .next()
        .unwrap()?
        .split(": ")
        .last()
        .unwrap()
        .parse()
        .unwrap();

    lines.next();

    let program: Vec<i64> = lines
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

    let a = get_values(&program, 0, b, c);

    println!("{}", a);

    Ok(())
}
