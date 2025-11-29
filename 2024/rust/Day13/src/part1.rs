use std::{
    env,
    fs::File,
    io::{self, prelude::*, BufReader},
    fmt
};

#[derive(Debug)]
struct Point {
    x: i64,
    y: i64,
}

impl fmt::Display for Point {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "({}, {})", self.x, self.y)
    }
}

impl Point {
    fn parse(str: String) -> Point {
        let parts: Vec<String> = str.split(", ").map(|s| s.to_string()).collect();

        if parts[0].contains('=') {
            Point {
                x: parts[0].split('=').last().unwrap().parse().unwrap(),
                y: parts[1].split('=').last().unwrap().parse().unwrap(),
            }
        } else {
            Point {
                x: parts[0].split('+').last().unwrap().parse().unwrap(),
                y: parts[1].split('+').last().unwrap().parse().unwrap(),
            }
        }
    }
}

fn get_score(a: Point, b: Point, loc: Point) -> i64 {
    let det: i64 = a.x * b.y - b.x * a.y;
    let a_n: i64 = loc.x * b.y - loc.y * b.x;
    let b_n: i64 = loc.x * a.y - loc.y * a.x;

    if det == 0 || a_n % det != 0 || b_n % det != 0 {
        return 0;
    }

    return 3 * a_n / det - b_n / det;
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

    let lines = reader.lines().map(|l| l.unwrap()).collect::<Vec<String>>();

    let mut total = 0;

    for chunks in lines.chunks(4) {
        let (a, b, loc) = (
                Point::parse(chunks[0].split(": ").last().unwrap().to_string()),
                Point::parse(chunks[1].split(": ").last().unwrap().to_string()),
                Point::parse(chunks[2].split(": ").last().unwrap().to_string()),
            );

        total += get_score(a, b, loc);
    }

    println!("{}", total);

    Ok(())
}
