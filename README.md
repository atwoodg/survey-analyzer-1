# Survey Analyzer Part 1 (Course Project)
 
## Overview
This project reads a student survey from stdin and outputs a specified format of response statistics to stdout.
Information is pulled from the survey text file with line-based input parsing, tokenization with `strtok`, simple aggregation in 2D arrays, and Unix-style CLI usage.

## Features
- Reads:
  - Output format (first non-comment line)
  - Survey questions/assertions (semicolon-separated)
  - Answer options (comma-separated)
  - Respondent answer rows (comma-separated)
- Computes per-question:
  - **Counts** per option (stored in a `props[question][option]` table)
  - **Average** score using a 1–4 scale
- Prints:
  - **(1,0)** → percent distribution per option
  - **(0,1)** → average score per question
  - **(1,1)** → both outputs

## Tech Stack
- C (C11)
- GCC
- stdio.h, string.h, stdlib.h
- Unix CLI

## Installation
Clone the repo and compile:

```bash
git clone https://github.com/atwoodg/survey-analyzer.git

cd survey-analyzer

gcc -std=c11 -Wall -Wextra -O2 survey.c -o survey
```

## How to use
Running the system:
```bash
cat tests/in01.txt | ./survey
cat tests/in02.txt | ./survey
cat tests/in03.txt | ./survey 
```

## Tests
To compare expected output and actual output:
```bash
cat tests/in01.txt | ./survey | diff tests/out01.txt -
cat tests/in02.txt | ./survey | diff tests/out02.txt -
cat tests/in03.txt | ./survey | diff tests/out03.txt - 
```

## Credits
- Contributors: Gabriel Atwood, Roberto Bittencourt
- Course: SENG 265 (Software Development Methods)


