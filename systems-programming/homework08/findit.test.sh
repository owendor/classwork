#!/bin/bash

WORKSPACE=/tmp/findit.$(id -u)
FAILURES=0
POINTS=4.00

error() {
    echo "$@"
    echo
    case "$@" in
        *Output*)
        printf "%-40s%-40s\n" "PROGRAM OUTPUT" "EXPECTED OUTPUT"
        cat $WORKSPACE/test.diff
        ;;
        *Valgrind*)
        echo
        cat $WORKSPACE/test.stderr
        ;;
    esac
    FAILURES=$((FAILURES + 1))
}

cleanup() {
    STATUS=${1:-$FAILURES}
    rm -fr $WORKSPACE
    exit $STATUS
}

export LD_LIBRARY_PATH=$LD_LIBRRARY_PATH:.

mkdir $WORKSPACE

trap "cleanup" EXIT
trap "cleanup 1" INT TERM

echo "Testing findit ..."

printf " %-60s ... " "findit"
valgrind --leak-check=full ./findit > $WORKSPACE/test.stdout 2> $WORKSPACE/test.stderr
if [ $? -eq 0 ]; then
    error "Failure (Exit Status)"
elif [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test.stderr) -ne 0 ]; then
    error "Failure (Valgrind)"
else
    echo "Success"
fi


FINDIT_PATH="/etc"

FINDIT_ARGS=""
printf " %-60s ... " "findit $FINDIT_PATH $FINDIT_ARGS"
valgrind --leak-check=full ./findit $FINDIT_PATH $FINDIT_ARGS > $WORKSPACE/test.stdout 2> $WORKSPACE/test.stderr
if [ $? -ne 0 ]; then
    error "Failure (Exit Status)"
elif [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test.stderr) -ne 0 ]; then
    error "Failure (Valgrind)"
elif ! diff -W 80 -y <(sort $WORKSPACE/test.stdout) <(find $FINDIT_PATH $FINDIT_ARGS 2> /dev/null | sort) &> $WORKSPACE/test.diff; then
    error "Failure (Output)"
else
    echo "Success"
fi


FINDIT_ARGS="-type f"
printf " %-60s ... " "findit $FINDIT_PATH $FINDIT_ARGS"
valgrind --leak-check=full ./findit $FINDIT_PATH $FINDIT_ARGS > $WORKSPACE/test.stdout 2> $WORKSPACE/test.stderr
if [ $? -ne 0 ]; then
    error "Failure (Exit Status)"
elif [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test.stderr) -ne 0 ]; then
    error "Failure (Valgrind)"
elif ! diff -W 80 -y <(sort $WORKSPACE/test.stdout) <(find $FINDIT_PATH $FINDIT_ARGS 2> /dev/null | sort) &> $WORKSPACE/test.diff; then
    error "Failure (Output)"
else
    echo "Success"
fi

FINDIT_ARGS="-type d"
printf " %-60s ... " "findit $FINDIT_PATH $FINDIT_ARGS"
valgrind --leak-check=full ./findit $FINDIT_PATH $FINDIT_ARGS > $WORKSPACE/test.stdout 2> $WORKSPACE/test.stderr
if [ $? -ne 0 ]; then
    error "Failure (Exit Status)"
elif [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test.stderr) -ne 0 ]; then
    error "Failure (Valgrind)"
elif ! diff -W 80 -y <(sort $WORKSPACE/test.stdout) <(find $FINDIT_PATH $FINDIT_ARGS 2> /dev/null | sort) &> $WORKSPACE/test.diff; then
    error "Failure (Output)"
else
    echo "Success"
fi

FINDIT_ARGS="-name '*.conf'"
printf " %-60s ... " "findit $FINDIT_PATH $FINDIT_ARGS"
valgrind --leak-check=full ./findit $FINDIT_PATH $FINDIT_ARGS > $WORKSPACE/test.stdout 2> $WORKSPACE/test.stderr
if [ $? -ne 0 ]; then
    error "Failure (Exit Status)"
elif [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test.stderr) -ne 0 ]; then
    error "Failure (Valgrind)"
elif ! diff -W 80 -y <(sort $WORKSPACE/test.stdout) <(find $FINDIT_PATH $FINDIT_ARGS 2> /dev/null | sort) &> $WORKSPACE/test.diff; then
    error "Failure (Output)"
else
    echo "Success"
fi


FINDIT_ARGS="-readable"
printf " %-60s ... " "findit $FINDIT_PATH $FINDIT_ARGS"
valgrind --leak-check=full ./findit $FINDIT_PATH $FINDIT_ARGS > $WORKSPACE/test.stdout 2> $WORKSPACE/test.stderr
if [ $? -ne 0 ]; then
    error "Failure (Exit Status)"
elif [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test.stderr) -ne 0 ]; then
    error "Failure (Valgrind)"
elif ! diff -W 80 -y <(sort $WORKSPACE/test.stdout) <(find $FINDIT_PATH $FINDIT_ARGS 2> /dev/null | sort) &> $WORKSPACE/test.diff; then
    error "Failure (Output)"
else
    echo "Success"
fi


FINDIT_ARGS="-writable"
printf " %-60s ... " "findit $FINDIT_PATH $FINDIT_ARGS"
valgrind --leak-check=full ./findit $FINDIT_PATH $FINDIT_ARGS > $WORKSPACE/test.stdout 2> $WORKSPACE/test.stderr
if [ $? -ne 0 ]; then
    error "Failure (Exit Status)"
elif [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test.stderr) -ne 0 ]; then
    error "Failure (Valgrind)"
elif ! diff -W 80 -y <(sort $WORKSPACE/test.stdout) <(find $FINDIT_PATH $FINDIT_ARGS 2> /dev/null | sort) &> $WORKSPACE/test.diff; then
    error "Failure (Output)"
else
    echo "Success"
fi


FINDIT_ARGS="-executable"
printf " %-60s ... " "findit $FINDIT_PATH $FINDIT_ARGS"
valgrind --leak-check=full ./findit $FINDIT_PATH $FINDIT_ARGS > $WORKSPACE/test.stdout 2> $WORKSPACE/test.stderr
if [ $? -ne 0 ]; then
    error "Failure (Exit Status)"
elif [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test.stderr) -ne 0 ]; then
    error "Failure (Valgrind)"
elif ! diff -W 80 -y <(sort $WORKSPACE/test.stdout) <(find $FINDIT_PATH $FINDIT_ARGS 2> /dev/null | sort) &> $WORKSPACE/test.diff; then
    error "Failure (Output)"
else
    echo "Success"
fi


FINDIT_ARGS="-type d -name '*.d'"
printf " %-60s ... " "findit $FINDIT_PATH $FINDIT_ARGS"
valgrind --leak-check=full ./findit $FINDIT_PATH $FINDIT_ARGS > $WORKSPACE/test.stdout 2> $WORKSPACE/test.stderr
if [ $? -ne 0 ]; then
    error "Failure (Exit Status)"
elif [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test.stderr) -ne 0 ]; then
    error "Failure (Valgrind)"
elif ! diff -W 80 -y <(sort $WORKSPACE/test.stdout) <(find $FINDIT_PATH $FINDIT_ARGS 2> /dev/null | sort) &> $WORKSPACE/test.diff; then
    error "Failure (Output)"
else
    echo "Success"
fi


FINDIT_ARGS="-type d -name '*.d' -executable"
printf " %-60s ... " "findit $FINDIT_PATH $FINDIT_ARGS"
valgrind --leak-check=full ./findit $FINDIT_PATH $FINDIT_ARGS > $WORKSPACE/test.stdout 2> $WORKSPACE/test.stderr
if [ $? -ne 0 ]; then
    error "Failure (Exit Status)"
elif [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test.stderr) -ne 0 ]; then
    error "Failure (Valgrind)"
elif ! diff -W 80 -y <(sort $WORKSPACE/test.stdout) <(find $FINDIT_PATH $FINDIT_ARGS 2> /dev/null | sort) &> $WORKSPACE/test.diff; then
    error "Failure (Output)"
else
    echo "Success"
fi


FINDIT_PATH="."

FINDIT_ARGS="-name '*.c'"
printf " %-60s ... " "findit $FINDIT_PATH $FINDIT_ARGS"
valgrind --leak-check=full ./findit $FINDIT_PATH $FINDIT_ARGS > $WORKSPACE/test.stdout 2> $WORKSPACE/test.stderr
if [ $? -ne 0 ]; then
    error "Failure (Exit Status)"
elif [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test.stderr) -ne 0 ]; then
    error "Failure (Valgrind)"
elif ! diff -W 80 -y <(sort $WORKSPACE/test.stdout) <(find $FINDIT_PATH $FINDIT_ARGS 2> /dev/null | sort) &> $WORKSPACE/test.diff; then
    error "Failure (Output)"
else
    echo "Success"
fi


FINDIT_ARGS="-writable"
printf " %-60s ... " "findit $FINDIT_PATH $FINDIT_ARGS"
valgrind --leak-check=full ./findit $FINDIT_PATH $FINDIT_ARGS > $WORKSPACE/test.stdout 2> $WORKSPACE/test.stderr
if [ $? -ne 0 ]; then
    error "Failure (Exit Status)"
elif [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test.stderr) -ne 0 ]; then
    error "Failure (Valgrind)"
elif ! diff -W 80 -y <(sort $WORKSPACE/test.stdout) <(find $FINDIT_PATH $FINDIT_ARGS 2> /dev/null | sort) &> $WORKSPACE/test.diff; then
    error "Failure (Output)"
else
    echo "Success"
fi


FINDIT_ARGS="-type f -name '*.unit' -executable"
printf " %-60s ... " "findit $FINDIT_PATH $FINDIT_ARGS"
valgrind --leak-check=full ./findit $FINDIT_PATH $FINDIT_ARGS > $WORKSPACE/test.stdout 2> $WORKSPACE/test.stderr
if [ $? -ne 0 ]; then
    error "Failure (Exit Status)"
elif [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test.stderr) -ne 0 ]; then
    error "Failure (Valgrind)"
elif ! diff -W 80 -y <(sort $WORKSPACE/test.stdout) <(find $FINDIT_PATH $FINDIT_ARGS 2> /dev/null | sort) &> $WORKSPACE/test.diff; then
    error "Failure (Output)"
else
    echo "Success"
fi


TESTS=$(($(grep -c Success $0) - 2))

echo
echo "   Score $(echo "scale=4; ($TESTS - $FAILURES) / $TESTS.0 * $POINTS" | bc | awk '{printf "%0.2f\n", $1}') / $POINTS"
printf "  Status "
if [ $FAILURES -gt 0 ]; then
    echo "Failure"
else
    echo "Success"
fi
echo
