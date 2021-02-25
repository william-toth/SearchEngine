#William Toth
#CS50, 21W
#Tester for Querier

#Refer to testquery 1 and testquery2 for testing conditions

make

echo "wrong number of arguments, invalid page directory, and invalid index file:"
./querier ../crawler/pageDirectory ../indexer/oldIndexFile thirdargument
./querier invalid_directory ../indexer/oldIndexFile
./querier ../crawler/pageDirectory invalid_file

echo "testquery 1: invalid queries (including digits and wrong and/or syntax): Should say that syntax is invalid"
./querier ../crawler/pageDirectory ../indexer/oldIndexFile < testquery1

echo "testquery 2: valid queries (to check score):"
./querier ../crawler/pageDirectory ../indexer/oldIndexFile < testquery2
