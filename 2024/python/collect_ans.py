from bs4 import BeautifulSoup as bs
import argparse
import requests


def main():
    # Parser setup
    parser = argparse.ArgumentParser(prog='collect_ans',
                                     description='Collect answers from AOC.',
                                     epilog='Blake Wingard - bats23456789@gmail.com')

    parser.add_argument('-s', '--session',
                        type=argparse.FileType('r'),
                        required=True,
                        help='The file containing the Session ID')
    parser.add_argument('-o', '--output',
                        type=argparse.FileType('w'),
                        required=False,
                        help='The file for output',
                        default='answers.txt')
    parser.add_argument('-d', '--day',
                        type=int,
                        default=1,
                        help='The day to parse')
    parser.add_argument('-y', '--year',
                        type=int,
                        default=2024,
                        help='The year to parse')

    args = parser.parse_args()

    # Session setup
    cookies = {
        'session': args.session.read().strip()
    }

    url = f"https://adventofcode.com/{args.year}/day/{args.day}"

    response = requests.get(url, cookies=cookies)
    page = bs(response.text, 'html.parser')
    answers = []

    for data in page.find_all('p'):
        if data.find('code') is not None and 'Your puzzle answer was' in data.get_text():
            for ans in data.find('code'):
                answers.append(ans)

    for (i, answer) in enumerate(answers):
        print(f"Part {i + 1}: {answer}", file=args.output)


if __name__ == "__main__":
    main()
