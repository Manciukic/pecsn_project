#!/usr/bin/env python3

import sys
from math import log

def print_usage():
    print(f"Usage: {sys.argv[0]} in.txt out.txt")

def main():
    if len(sys.argv) < 3:
        print_usage()
        sys.exit(1)

    with open(sys.argv[1], "r") as fin:
        with open(sys.argv[2], "w") as fout:
            for line in fin.readlines():
                first = True
                for value in line.split(" "):
                    try:
                        # print('"'+value+'"')
                        fvalue = float(value)
                        lvalue = log(fvalue)
                        if not first:
                            fout.write(" ")
                        else:
                            first = False
                        slvalue = "%f" % lvalue
                        # print(slvalue)
                        # print()
                        fout.write(slvalue)
                    except:
                        # print("NaN")
                        # print()
                        pass
                fout.write("\n")

if __name__ == "__main__":
    main()
