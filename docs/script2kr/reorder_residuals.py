#!/usr/bin/env python3

import sys

def get_bit(i, n):
    return (n>>i)%2

def conversion(n, k=4):
    s = 0
    for i in range(k):
        if not get_bit(i, n):
            s += 2**(k-i-1)
    print(f"{n} becomes {s} (k={k})")
    return s

def print_usage():
    print(f"Usage: {sys.argv[0]} in.txt out.txt k r")

def main():
    if len(sys.argv) < 5:
        print_usage()
        sys.exit(1)

    k = int(sys.argv[3])
    r = int(sys.argv[4])
    
    with open(sys.argv[1], 'r') as f:
        lines = f.readlines()
    
    with open(sys.argv[2], 'w') as f:
        for i, line in enumerate(lines):
            v = line.split()[1]
            n = conversion(i//r,k)*r + i%r 
            f.write(f"{n} {v}\n")

if __name__ == "__main__":
    main()
