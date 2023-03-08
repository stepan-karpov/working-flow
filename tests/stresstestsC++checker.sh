#!/bin/bash
cd /Users/stepan/Desktop/Code/working-flow/tests/
g++ -std=c++17 create_test.cpp -o create_test.trash
g++ -std=c++17 incorrect_program.cpp -o incorrect_program.trash
g++ -std=c++17 checker.cpp -o checker.trash

> log.txt

for (( counter=0;  counter<=3000; counter++ )); do
  ./create_test.trash > test.txt
  ./incorrect_program.trash < test.txt > incorrect_answer.txt
    if (( $counter % 10 == 0 )); then
      echo "passing test $counter" >> log.txt
    fi
  ./checker.trash < test.txt >> log.txt
done