#!/bin/bash
cd /Users/stepan/Desktop/Code/working-flow/tests/
g++ -std=c++17 create_test.cpp -o create_test.cppWithExt
g++ -std=c++17 incorrect_program.cpp -o incorrect_program.cppWithExt
g++ -std=c++17 checker.cpp -o checker.cppWithExt

> log.txt

for (( counter=0;  counter<=3000; counter++ )); do
  ./create_test.cppWithExt > test.txt
  ./incorrect_program.cppWithExt < test.txt > incorrect_answer.txt
    if (( $counter % 10 == 0 )); then
      echo "passing test $counter" >> log.txt
    fi
  ./checker.cppWithExt < test.txt >> log.txt
done