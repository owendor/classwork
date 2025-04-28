#!/bin/sh

# Globals

URL=https://www.zipcodestogo.com/
CITY="0"
STATE="Indiana"

# Functions

usage() {
    cat 1>&2 <<EOF
Usage: $(basename $0)

-c      CITY    Which city to search
-s      STATE   Which state to search ($STATE)

If no CITY is specified, then all the zip codes for the STATE are displayed.
EOF
    exit $1
}

zipcode_information() {
    # Fetch zipcode information from URL based on CITY and STATE
    curl -sL "$URL$STATE/"
}

filter_zipcodes() {
    # Extract zipcodes from zipcode source
    if [ "$CITY" == "0" ]; then
       grep -Eo '/[0-9]{5}/' | tr -d '/'
    else
       grep -Eo "/$CITY/[a-zA-Z]+/[0-9]{5}/" | grep -Eo '[0-9]{5}'
    fi
}

# Parse Command Line Options

while [ $# -gt 0 ]; do
    case $1 in
        -s)
            shift
	    STATE=""
            while [ $# -gt 0 ] && [ "${1#-}" = "$1" ]; do
                STATE+="$1"
                shift
            done
            
            STATE=${STATE[*]}
            STATE=${STATE// /%20}
            ;;
        -c)
            shift
	    CITY=""
            while [ $# -gt 0 ] && [ "${1#-}" = "$1" ]; do
                CITY+="$1"
                shift
            done
            
            CITY="${CITY[*]}"
            ;;
        -h) usage 0;;
        *)  usage 1;;
    esac
done

# Filter Pipeline

zipcode_information | filter_zipcodes 
