#!/bin/bash
COUNTER_SUCCESS=0
COUNTER_FAIL=0
TEST_FILE1="./test_files/1.txt"
TEST_FILE2="./test_files/1.txt ./test_files/2.txt ./test_files/3.txt ./test_files/test.txt"
PATTERN1="a"
PATTERN2="test"

flags_array=(-i -v -c -l -n -e -s -h)

echo "Testing processing. Wait..."

for var in ${flags_array[@]}
do
    TEST="$var $PATTERN2 $TEST_FILE2"
    ./s21_grep $TEST > s21_grep.txt
    grep $TEST > grep.txt
    DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
    if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
        then
            ((COUNTER_SUCCESS++))
        else
            echo "Test case $var failed"
            ((COUNTER_FAIL++))
    fi
done

rm s21_grep.txt grep.txt
echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"
