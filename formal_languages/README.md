## This folder in my github directory contains task #5 from homework #3

####Brief task implementation overview:
  - ##### dka_transformer.cpp
    
    > this file contains code itself. *Required language: c++20*
    
    >If you want to use it, just read the instructions given in the output in console
    >example of an automaton description:

    ```2 3     - number of vertexes, number of edges
    0 1 `   - there is an edge from vertex #0 to vertex #1 with a letter ` (eps)
    1 0 a   - there is an edge from vertex #1 to vertex #0 with a letter a
    0 0 a   - there is an edge from vertex #0 to vertex #0 with a letter a
    1       - the amount of terminal vertexes
    0       - number of vertex itself
    ```

    >the output will be represented in the same format with extended description

  - ##### tests/

    >As it was asked, this repository also contains test coverage.
    There are two tests (tests/test1-eps.txt, tests/test2-thompson.txt) which were checked manually

    >There is also an automation testing. To initialize it, write a proper way go the folder formal_languages/tests in tests/stresstestsC++.sh in line 2. Then simply run bash script. Be sure that you have g++ supporting c++20

    >I've configured automatically 10'000 tests, each test contain NKA and 1'000 words 0-15 length each. If a recognition stays on this set of 1'000 words stays the same after NKA->DKA transform, then the test is passed. As you can see in log.txt file, the testing was done successfully and took ~30 minutes.

    >>correct_program.cpp     checks if there is possible to recognize a word with automaton

    >> create_test.cpp         creates test

    >> incorrect_program.cpp   completes NKA->DKA transform and checks recognition

    >> stresstestsC++.sh       initiates testing


    



  