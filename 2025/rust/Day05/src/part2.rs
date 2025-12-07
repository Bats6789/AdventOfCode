use std::{
    env,
    fs::File,
    io::{self, BufReader, prelude::*},
    str::FromStr,
};

#[derive(Debug)]
#[derive(Clone)]
#[derive(Copy)]
struct Range {
    start: i64,
    stop: i64,
}

impl Range {
    fn inside(&self, target: &Range) -> bool {
        return self.value_inside(target.start) || self.value_inside(target.stop);
    }

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

    let ranges: Vec<Range> = range_str
        .lines()
        .filter_map(|line| line.parse::<Range>().ok())
        .collect();

    let mut com_ranges: Vec<Range> = Vec::with_capacity(ranges.len());

    let mut count = 0;

    for mut range in ranges {
        let mut did_compress = true;
        while did_compress {
            did_compress = false;

            for (i, com_range) in com_ranges.clone().iter().enumerate() {
                if range.inside(&com_range) || com_range.inside(&range) {
                    range.start = range.start.min(com_range.start);
                    range.stop = range.stop.max(com_range.stop);
                    com_ranges.remove(i);
                    did_compress = true;
                    break;
                }
            }

            if !did_compress {
                com_ranges.push(range);
            }
        }
    }

    for com_range in com_ranges {
        count += com_range.stop - com_range.start + 1;
    }

    println!("{}", count);

    Ok(())
}
