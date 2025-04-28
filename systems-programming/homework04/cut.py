#!/usr/bin/env python3

''' cut.py - remove sections from each line of stream '''

import io
import sys

# Functions

def usage(exit_status: int=0) -> None:
    ''' Print usage message and exit. '''
    print('''Usage: cut -d DELIMITER -f FIELDS

Print selected parts of lines from stream to standard output.

    -d DELIMITER     Use DELIM instead of TAB for field delimiter
    -f FIELDS        Select only these fields''', file=sys.stderr)
    sys.exit(exit_status)

def strs_to_ints(strings: list[str]) -> list[int]:
    ''' Convert all strings in list to integers.

    >>> strs_to_ints(['2', '4'])
    [2, 4]
    '''

    int_list = []

    for string in strings:
        int_list.append(int(string))

    return int_list

def cut_line(line: str, delimiter: str='\t', fields: list[int]=[]) -> list[str]:
    ''' Return selected fields from line separated by delimiter.

    >>> cut_line('Harder, Better, Faster, Stronger', ',', [2, 4])
    [' Better', ' Stronger']
    '''
    
    parts = line.split(delimiter)
    selected = []
    for field in fields:
        index = field - 1
        if 0 <= index < len(parts):
            selected.append(parts[index])
    
    return selected

def cut_stream(stream=sys.stdin, delimiter: str='\t', fields: list[int]=[]) -> None:
    ''' Print selected parts of lines from stream to standard output.

    >>> cut_stream(io.StringIO('Harder, Better, Faster, Stronger'), ',', [2, 4])
     Better, Stronger
    '''

    for line in stream:
        selected = cut_line(line.rstrip(), delimiter, fields)
        print(*selected, sep=delimiter) # Changed this line

# Main Execution

def main(arguments=sys.argv[1:], stream=sys.stdin) -> None:
    ''' Print selected parts of lines from stream to standard output.

    This function will parse the command line arguments to determine the
    delimiter and which fields to select from each line.

    >>> main('-d , -f 2,4'.split(), io.StringIO('Harder, Better, Faster, Stronger'))
     Better, Stronger
    '''
    # Parse command line arguments
    delimiter = '\t'
    fields = []

    args_iter = iter(arguments)
    for arg in arguments:
        if arg == '-h':
            usage(0)
        elif arg == '-d':
            i = arguments.index(arg)
            if i + 1 < len(arguments):
                delimiter = arguments[i + 1]
        elif arg == '-f':
            i = arguments.index(arg)
            if i + 1 < len(arguments):
                fields = strs_to_ints(arguments[i + 1].split(','))
        elif arg.startswith('-'):
            usage(1)

    if not fields:
        usage(1)

    # Cut stream with delimiter and fields
    cut_stream(stream, delimiter, fields)

if __name__ == '__main__':
    main()

# vim: set sts=4 sw=4 ts=8 expandtab ft=python: