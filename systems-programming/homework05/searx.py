#!/usr/bin/env python3

''' searx.py - SearX from the command line '''

import sys

import requests

# Constants

URL     = 'https://searx.ndlug.org/search'
LIMIT   = 5
ORDERBY = 'score'

# Functions

def usage(exit_status: int=0) -> None:
    ''' Print usage message and exit. '''
    print(f'''Usage: searx.py [-u URL -n LIMIT -o ORDERBY] QUERY

Fetch SearX results for QUERY and print them out.

    -u URL      Use URL as the SearX instance (default is: {URL})
    -n LIMIT    Only display up to LIMIT results (default is: {LIMIT})
    -o ORDERBY  Sort the search results by ORDERBY (default is: {ORDERBY})

If ORDERBY is score, the results are shown in descending order.  Otherwise,
results are shown in ascending order.''', file=sys.stderr)
    sys.exit(exit_status)

def searx_query(query: str, url: str=URL) -> list[dict]:
    ''' Returns lists of results for query from SearX.

    >>> searx_query('Python', 'https://yld.me/iB1T') # doctest: +ELLIPSIS
    [{'url': 'https://www.python.org/', 'title': 'Welcome to Python.org', ...}]
    '''

    parameters = {'q': query, 'format': 'json'}
    response = requests.get(url, params=parameters)
    return response.json()['results']

def print_results(results: list[dict], limit: int=LIMIT, orderby: str=ORDERBY) -> None:
    ''' Print results of SearX query.

    >>> print_results(searx_query('Python', 'https://yld.me/iB1T')) # doctest: +ELLIPSIS, +NORMALIZE_WHITESPACE
        1.  Welcome to Python.org [...]
            https://www.python.org/
    ...
    '''

    sorted_results = sorted(results, key=lambda x: x[orderby], reverse=(orderby=='score'))

    for index, result in enumerate(sorted_results[:limit], 1):
        print(f"{index:>4}.\t{result['title']} [{result['score']:0.2f}]")
        print(f"\t{result['url']}")
        if index < len(sorted_results[:limit]): # only prints new line between items
            print()

# Main Execution

def main(arguments=sys.argv[1:]) -> None:
    ''' Searches SearX and print results.

    >>> main('-u https://yld.me/iB1T Python'.split()) # doctest: +ELLIPSIS, +NORMALIZE_WHITESPACE
        1.  Welcome to Python.org [...]
            https://www.python.org/
    ...
    '''

    # Set variables equal to the constants (initially)
    url = URL
    limit = LIMIT
    orderby = ORDERBY

    search_terms = []

    i = 0
    while i < len(arguments):
        arg = arguments[i]

        if arg == '-u':
            url = arguments[i+1]
            i += 2
        elif arg == '-n':
            limit = int(arguments[i+1]) # convert the argument to int before setting limit
            i += 2
        elif arg == '-o':
            orderby = arguments[i+1]
            i += 2
        elif arg == '-h':
            usage(0)
        elif arg.startswith('-'): # handles case where user enters an invalid command
            usage(1)
        else: # if it's not a command and it's not invalid, I can assume it's a search term
            search_terms.append(arg)
            i += 1

    # Display the usage message if the user didn't enter a search term
    if not search_terms:
        usage(1)

    query = ' '.join(search_terms)
    results = searx_query(query, url)
    print_results(results, limit, orderby)

if __name__ == '__main__':
    main()

# vim: set sts=4 sw=4 ts=8 expandtab ft=python: