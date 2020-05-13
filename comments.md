-2 Your CSV formatting is incorrect - should not have trailing commas, which
should only be between solution values

-2 In cases where your solvers share implementation (e.g. in your print function),
 that code should not be duplicated

-1 Don't name variables after C++ keywords - in your cholesky class, you have a
local variable named "final"

-2 Your forcing function should be a callback instead of a scalar

-2 Your code doesn't support arbitrary boundary conditions (e.g. for when there is
a black pixel on the edge of the image)


Your score is:
91
