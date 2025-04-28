#!/usr/bin/env python3

''' wc.py - print newline, word, and byte counts for stream '''

import io
import sys

# Functions

def usage(exit_status: int=0) -> None:
    ''' Print usage message and exit. '''
    print('''Usage: wc.py [-l | -w | -c]

Print newline, word, and byte counts from standard input.

The options below may be used to select which counts are printed, always in
the following order: newline, word, byte.

    -c      Print byte counts
    -l      Print newline counts
    -w      Print word counts''', file=sys.stderr)
    sys.exit(exit_status)

def count_stream(stream=sys.stdin) -> dict[str, int]:
    ''' Count the newlines, words, and bytes in specified stream.

    >>> count_stream(io.StringIO('Despite all my rage, I am still just a rat in a cage'))
    {'newlines': 1, 'words': 13, 'bytes': 52}
    '''
    counts = {'newlines': 0, 'words': 0, 'bytes': 0}
    for line in stream:
        counts['newlines'] += 1
        counts['bytes'] += len(line.encode('utf-8')) # found this byte-counting solution online
        words = line.split()
        counts['words'] += len(words)
    return counts

def print_counts(counts: dict[str, int], options: list[str]) -> None:
    ''' Print the newline, word, and byte counts.  If none of the options are
    specified, then include all options in output.  Othewrise, only include the
    specified options.

    Note: always output the counts the following order: newlines, words, bytes.

    >>> print_counts({'newlines': 1, 'words': 13, 'bytes': 52}, ['newlines', 'words', 'bytes'])
     1 13 52
    '''
    
    output_order = ['newlines', 'words', 'bytes']
    counts_to_print = []
        
    if not options:
        options = output_order
        
    # Add selected counts to counts_to_print
    for option in output_order:
        if option in options:
            counts_to_print.append(counts[option])
    
    # This calculates the width based off of all the the counts
    if len(counts_to_print) > 1:
        max_all = max(counts.values())
        count_width = len(str(max_all))
    else:
        count_width = 0
    
    # Format the selected counts and join with spaces
    formatted_counts = [str(count).rjust(count_width) for count in counts_to_print]
        
    output_string = ' '.join(formatted_counts)
    print(output_string)

# Main Execution

def main(arguments=sys.argv[1:], stream=sys.stdin) -> None:
    ''' Print the newline, word, and byte counts from stream.

    This function will parse the command line arguments to select which counts
    to include in the final report.

    >>> main([], io.StringIO('Despite all my rage, I am still just a rat in a cage'))
     1 13 52
    '''
    # Parse command line arguments
    options = []
    for arg in arguments:
        if arg in ('-h', '--help'):
            usage(0)
        elif arg in ('-c', '--bytes'):
            options.append('bytes')
        elif arg in ('-l', '--lines'):
            options.append('newlines')
        elif arg in ('-w', '--words'):
            options.append('words')
        else:
            usage(1)

    # Count stream and print counts
    counts = count_stream(stream)
    print_counts(counts, options)

if __name__ == '__main__':
    main()

# vim: set sts=4 sw=4 ts=8 expandtab ft=python:
