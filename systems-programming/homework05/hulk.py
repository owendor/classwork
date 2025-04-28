#!/usr/bin/env python3

from typing import Iterable, Iterator

import concurrent.futures
import hashlib
import os
import string
import sys

# Constants

ALPHABET = string.ascii_lowercase + string.digits

# Functions

def usage(exit_code: int=0):
    print('''Usage: hulk.py [-a ALPHABET -c CORES -l LENGTH -p PATH -s HASHES]
    -a ALPHABET Alphabet to use in permutations
    -c CORES    CPU Cores to use
    -l LENGTH   Length of permutations
    -p PREFIX   Prefix for all permutations
    -s HASHES   Path of hashes file''', file=sys.stderr)
    sys.exit(exit_code)

def sha1sum(s: str) -> str:
    ''' Compute SHA1 digest for given string.

    >>> sha1sum('a')
    '86f7e437faa5a7fce15d1ddcb9eaeaea377667b8'
    '''
    hashOfString = hashlib.sha1()
    hashOfString.update(s.encode('utf-8'))
    return hashOfString.hexdigest()

def permutations(length: int, alphabet: str=ALPHABET) -> Iterator[str]:
    ''' Recursively yield all permutations of alphabet up to given length.

    >>> for p in permutations(2, 'ab'): print(p)
    aa
    ab
    ba
    bb
    '''
    if length == 0:   # Base case
        yield ''
    else:             # Recursive case
        for prefix in alphabet:
            for suffix in permutations(length - 1, alphabet):
                yield prefix + suffix # this can be done in one line but I think this is more readble

def flatten(sequence: Iterable[Iterable[str]]) -> Iterator[str]:
    ''' Flatten sequence of iterables.

    >>> for p in flatten([['a', 'b'], ['c', 'd']]): print(p)
    a
    b
    c
    d
    '''
    for sub_iterable in sequence:
            yield from sub_iterable



def crack(hashes: set[str], length: int, alphabet: str=ALPHABET, prefix: str='') -> list[str]:
    ''' Return all password permutations of specified length that are in hashes
    by trying all possible permutations sequentially.

    >>> for p in crack({sha1sum(l) for l in 'abc'}, 1, 'abcd'): print(p)
    a
    b
    c
    '''
    matches = []
    for perm in permutations(length, alphabet):
        candidate = prefix + perm
        if sha1sum(candidate) in hashes:
            matches.append(candidate)
    return matches



def whack(arguments: tuple[set[str], int, str, str]) -> list[str]:
    ''' Call the crack function with the specified list of arguments

    >>> for p in whack([{sha1sum(l) for l in 'abc'}, 1, 'abcd', '']): print(p)
    a
    b
    c
    '''
    hashes, length, alphabet, prefix = arguments
    return crack(hashes, length, alphabet, prefix)

def smash(hashes: set[str], length: int, alphabet: str=ALPHABET, prefix: str='', cores: int=1) -> Iterator[str]:
    ''' Return all password permutations of specified length that are in hashes
    by cracking subsets of all possible permutations concurrently.

    >>> for p in smash({sha1sum(l) for l in 'abc'}, 1, 'abcd'): print(p)
    a
    b
    c
    '''
    arguments = ((hashes, length-1, alphabet, prefix + p) for p in alphabet)

    # Use the ProcessPoolExecutor to make use of mutliple cores (specified by user)
    with concurrent.futures.ProcessPoolExecutor(cores) as executor:
        results = executor.map(whack, arguments)

    return flatten(results) # return results after flattening them



# Main Execution

def main(arguments: list[str]=sys.argv[1:]) -> None:
    ''' Smashes given hashes to determine passwords with specified alphabet,
    length, and prefix.  Uses multiple cores (ie. processes) if specified.

    >>> main('-a abcdefg -l 2'.split())
    cg
    fg
    gg
    '''
    alphabet    = ALPHABET
    cores       = 1
    hashes_path = 'hulk.hashes'
    length      = 1
    prefix      = ''

    # Parse command line arguments (I use the same while loop structure as searx.py)
    i = 0
    while i < len(arguments):
        arg = arguments[i]

        if arg == '-a':
            alphabet = arguments[i+1]
            i += 2
        elif arg == '-c':
            cores = int(arguments[i+1])
            i += 2
        elif arg == '-l':
            length = int(arguments[i+1])
            i += 2
        elif arg == '-p':
            prefix = arguments[i+1]
            i += 2
        elif arg == '-s':
            hashes_path = arguments[i+1]
            i += 2
        elif arg == '-h':
            usage(0)
        else:
            usage(1)

    # Load hashes set
    hashes = set()
    with open(hashes_path) as hashfile:
        for line in hashfile:
            hashes.add(line.strip())

    # Execute smash function and store results
    results = smash(hashes, length, alphabet, prefix, cores)

    # Print all found passwords
    for password in results:
        print(password)


if __name__ == '__main__':
    main()

# vim: set sts=4 sw=4 ts=8 expandtab ft=python:
