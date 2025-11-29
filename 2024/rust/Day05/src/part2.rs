use std::{
    collections::HashMap,
    env,
    fs::File,
    io::{self, prelude::*, BufReader},
};

fn is_valid(list: &Vec<u64>, orders: &HashMap<u64, Vec<u64>>) -> bool {
    let mut seen: HashMap<u64, bool> = HashMap::new();

    for item in list {
        for check in orders.get(item).unwrap().iter() {
            if seen.contains_key(check) {
                return false;
            }
        }
        seen.insert(*item, true);
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
    let mut reader = BufReader::new(file);
    let mut contents = String::new();
    let _ = reader.read_to_string(&mut contents);

    let mut parts = contents.split("\r\n\r\n");

    let orders_str = parts.next().unwrap();
    let lists_str = parts.next().unwrap();

    let mut total: u64 = 0;

    let mut orders: HashMap<u64, Vec<u64>> = HashMap::new();

    for order_str in orders_str.lines() {
        let mut parts = order_str.split('|').map(|i| i.parse::<u64>().unwrap());
        let key = parts.next().unwrap();
        let value = parts.next().unwrap();

        if !orders.contains_key(&key) {
            orders.insert(key, Vec::new());
        }
        orders.get_mut(&key).unwrap().push(value);
    }

    let lists: Vec<Vec<u64>> = lists_str
        .lines()
        .map(|l| l.split(',').map(|i| i.parse::<u64>().unwrap()).collect())
        .collect();

    for mut list in lists {
        if !is_valid(&list, &orders) {
            while !is_valid(&list, &orders) {
                let mut seen: HashMap<u64, bool> = HashMap::new();
                let mut skip = false;

                // let mut i = 0;
                let mut j = 0;
                for (i, item) in list.iter().enumerate() {
                    for check in orders.get(&item).unwrap().iter() {
                        if seen.contains_key(check) {
                            j = list.iter().position(|r| r == check).unwrap();
                            skip = true;
                            break;
                        }
                    }
                    if skip {
                        let tmp = list[i];
                        list[i] = list[j];
                        list[j] = tmp;
                        break;
                    }
                    seen.insert(*item, true);
                }
            }
            total += list[list.len() / 2];
        }
    }

    println!("{}", total);

    Ok(())
}
