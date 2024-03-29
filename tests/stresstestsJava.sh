#!/bin/bash
cd /Users/stepan/Desktop/Code/working-flow/tests/
g++ -std=c++17 create_test.cpp -o create_test.trash
g++ -std=c++17 correct_program.cpp -o correct_program.trash
javac incorrect_program.java

> log.txt

for (( counter=0;  counter<=3000; counter++ )); do
  ./create_test.trash > test.txt
  ./correct_program.trash < test.txt > right_answer.txt
  java incorrect_program < test.txt > incorrect_answer.txt
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