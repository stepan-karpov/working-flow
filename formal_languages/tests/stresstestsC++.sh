#!/bin/bash
cd /Users/stepan/Desktop/working-flow/formal_languages/tests
g++ -std=c++20 create_test.cpp -o create_test.trash
g++ -std=c++20 correct_program.cpp -o correct_program.trash
g++  -fsanitize=undefined -fsanitize=address -std=c++20 incorrect_program.cpp -o incorrect_program.trash

> log.txt

for (( counter=0;  counter<=10000; counter++ )); do
  ./create_test.trash > test.txt
  ./correct_program.trash < test.txt > right_answer.txt
  ./incorrect_program.trash < test.txt > incorrect_answer.txt
  content1=`cat right_answer.txt`
  content2=`cat incorrect_answer.txt`
  if [ "$content1" != "$content2" ]; then
    echo "Warning: test is incorrect" >> log.txt
    echo "======== test ========" >> log.txt
    echo `cat test.txt` >> log.txt
    echo "======================" >> log.txt
    echo "right answer is: " >> log.txt
    echo "$content1" >> log.txt
    echo "=====================" >> log.txt
    echo "your answer is: " >> log.txt
    echo "$content2" >> log.txt
    echo >> log.txt
  else
    if (( $counter % 10 == 0 )); then
      echo "$counter test is ok" >> log.txt
    fi
  fi
done