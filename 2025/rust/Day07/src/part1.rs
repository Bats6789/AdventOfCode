use std::{
    collections::HashSet,
    env,
    fs::File,
    io::{self, BufReader, prelude::*},
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

    let mut lines = reader.lines();

    let mut beams: HashSet<i64> = HashSet::new();

    beams.insert(
        lines
            .next()
            .expect("Failed to extract next")
            .expect("Failed to extract next")
            .find('S')
            .expect("Failed to find 'S'") as i64,
    );

    let mut count = 0;

    for line in lines {
        let mut new_beams: HashSet<i64> = HashSet::new();
        let line: Vec<char> = line?.chars().collect();
        for &beam in beams.iter() {
            if 0 <= beam && beam <= line.len() as i64 && line[beam as usize] == '^' {
                count += 1;
                new_beams.insert(beam - 1);
                new_beams.insert(beam + 1);
            } else {
                new_beams.insert(beam);
            }
        }
        beams = new_beams;
    }

    println!("{}", count);

    Ok(())
}
