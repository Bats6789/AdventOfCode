use std::{
    env,
    fs::File,
    io::{self, BufReader, prelude::*},
    str::FromStr,
};

#[derive(Debug)]
struct Range {
    start: i64,
    stop: i64,
}

impl Range {
    fn value_inside(&self, target: i64) -> bool {
        return self.start <= target && target <= self.stop;
    }
}

impl FromStr for Range {
    type Err = String;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let parts: Vec<&str> = s.split('-').collect();
        if parts.len() == 2 {
            let start = parts[0].parse::<i64>().map_err(|e| e.to_string())?;
            let stop = parts[1].parse::<i64>().map_err(|e| e.to_string())?;
            return Ok(Range { start, stop });
        } else {
            return Err("Invalid format: expected 'start-stop'".to_string());
        }
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
    let mut reader = BufReader::new(file);
    let mut content = String::new();

    let _ = reader.read_to_string(&mut content);

    let mut splits = content.split("\n\n");

    let range_str = splits.next().expect("Failed to extract range_str");
    let ids_str = splits.next().expect("Failed to extract ids_str");

    let ranges: Vec<Range> = range_str
        .lines()
        .filter_map(|line| line.parse::<Range>().ok())
        .collect();

    let ids: Vec<i64> = ids_str
        .lines()
        .filter_map(|line| line.parse::<i64>().ok())
        .collect();

    let mut count = 0;

    for id in ids {
        for range in &ranges {
            if range.value_inside(id) {
                count += 1;
                break;
            }
        }
    }

    println!("{}", count);

    Ok(())
}
