## README for crawler

To use, simply run `make` and then `make test`. However, you must modify the test target and change the arguments when if you would like to try with different arguments. Currently, the program is set to run 10+ different test programs.

To view test results for the test cases alteady in makefile/testing.sh, refer to testing.out. These test results are primarily hashtables of urls seen or a stderr message with inability to create target (for test cases that are supposed to fail).

To view the html files saved for your test, Navigate to the `pageDirectory`, which should have files for each page with a unique `id` number once you have run `make` and `make test`. By default, the files for the current test in `Makefile` are saved in this directory.
