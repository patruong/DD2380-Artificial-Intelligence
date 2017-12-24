#!/usr/bin/env python3


# TODO gen A, B or pi depending on sys.argv[1] == "A", etc. ??

import sys
import random as rnd

args = sys.argv[1:]


if len(args) >= 1:
    n = int(args[0])
else:
    n = rnd.randint(0,10)

if len(args) >= 2:
    m = int(args[1])
else:
    m = rnd.randint(0,10)

M = [[rnd.random() for c in range(m)] for r in range(n)]

for r in range(n):
    tot = sum(M[r])
    M[r] = [x/tot for x in M[r]]

print(n, m, *[M[r][c] for r in range(n) for c in range(m)])
