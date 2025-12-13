use std::{
    collections::HashMap,
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

    let mut beams: HashMap<i64, i64> = HashMap::new();

    beams.insert(
        lines
            .next()
            .expect("Failed to extract next")
            .expect("Failed to extract next")
            .find('S')
            .expect("Failed to find 'S'") as i64,
            1
    );

    for line in lines {
        let mut new_beams: HashMap<i64, i64> = HashMap::new();
        let line: Vec<char> = line?.chars().collect();
        for (&beam, &count) in &beams {
            if 0 <= beam && beam <= line.len() as i64 && line[beam as usize] == '^' {
                new_beams.insert(beam - 1, new_beams.get(&(beam - 1)).unwrap_or(&0) + count);
                new_beams.insert(beam + 1, new_beams.get(&(beam + 1)).unwrap_or(&0) + count);
            } else {
                new_beams.insert(beam, new_beams.get(&beam).unwrap_or(&0) + count);
            }
        }
        beams = new_beams;
    }

    println!("{}", beams.values().sum::<i64>());

    Ok(())
}
