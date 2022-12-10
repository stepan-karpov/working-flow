#!/bin/bash
cd /Users/stepan/Desktop/Code/working-flow/tests/
g++ -std=c++17 create_test.cpp -o create_test.cppWithExt
g++ -std=c++17 correct_program.cpp -o correct_program.cppWithExt
g++ -std=c++17 incorrect_program.cpp -o incorrect_program.cppWithExt

> log.txt

for (( counter=0; counter<=300; counter++ )); do
  ./create_test.cppWithExt > test.txt
  ./correct_program.cppWithExt < test.txt > right_answer.txt
  ./incorrect_program.cppWithExt < test.txt > incorrect_answer.txt
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