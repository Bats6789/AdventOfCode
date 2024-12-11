use std::{
    env,
    fs::File,
    io::{self, prelude::*, BufReader},
};

#[derive(Copy, Clone, Debug)]
struct Chunk {
    id: i64,
    free: bool,
    rep: usize
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

    let mut line = String::new();

    let _ = reader.read_to_string(&mut line);

    let mut disk: Vec<Chunk> = Vec::new();
    let mut chunk: Chunk = Chunk {id: 0, free: false, rep: 0};
    let mut check_sum = 0;

    for c in line.chars() {
        if c.is_whitespace() {
            continue;
        }

        chunk.rep = c.to_digit(10).unwrap() as usize;
        disk.push(chunk);
        
        if chunk.free {
            chunk.id += 1;
            chunk.free = false;
        } else {
            chunk.free = true;
        }
    }

    let mut i = 0;

    while i < disk.len() {
        if disk[i].free {
            let mut j = disk.len() - 1;

            while j > i {
                if !disk[j].free {
                    if disk[j].rep >= disk[i].rep {
                        disk[i].id = disk[j].id;
                        disk[i].free = false;
                        disk[j].rep -= disk[i].rep;
                        break;
                    } else {
                        let tmp = disk[j];
                        disk[j].free = true;
                        disk[i].rep -= disk[j].rep;
                        disk.insert(i, tmp);
                        i += 1;
                        j += 1;
                    }
                }
                j -= 1;
            }
        }
        i += 1;
    }

    i = 0;
    for item in disk {
        if item.free {
            break;
        }

        for _ in 0..item.rep {
            check_sum += (i as i64) * item.id;
            i += 1;
        }
    }

    println!("{}", check_sum);

    Ok(())
}
