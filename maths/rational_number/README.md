Program to represent a real number, R, as a ratio of two integers, a and b.

Originally it was to determine if a number was rational, but good luck giving a computer an irrational number? I think I'd have to write a paper studying that. Maybe later :)

Where R denotes a real number, 
    -inf \< R \> inf

1. R \< 0
    a. R \< -1, |-a| \> b, or a \> |-b| 
    b. -1 \<= R \< 0, |-a| \< b, or a \< |-b|

2. R \>= 0
    a. 0 \<= R \< 1, a \< b, or |-a| \< |-b|
    b. 1 \<= R, a \> b, or |-a| \> |-b|

In cases 2a and 2b, we can discard |-a| and |-b|, since we are deciding a and b as our output.

In terms of a way to find the ratio of a and b to compose the input, I will start by casting the double as an integer. With from this, I can do a iterative search where I slowly hone in on the correct ratio. I imagine it will look something like a binary search