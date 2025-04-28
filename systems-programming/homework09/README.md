# Homework 09

AI Code Review:

I asked the AI to review the parse_options function in timeit.c

The AI suggested better error handling for the timeout value, as well as better error handling for unknown options and more efficient string copying for the commands. I don't think there needs to be better error handling for unknown options since the usage function is called for any erroneous function call. I liked using memcpy to more efficiently copy the commands, though, so I implemented it (without the malloc error check, since this shouldn't fail).

## Acknowledgments

> List anyone you collaborated with or received help from (including TAs, other
students, and AI tools)
