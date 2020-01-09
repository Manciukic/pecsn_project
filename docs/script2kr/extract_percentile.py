#!/usr/bin/env python3
"""
Extracts nth percentile from omnet vec files and appends it to the corresponding
scalar file.
"""

import sys
import numpy as np
import argparse

parser = argparse.ArgumentParser(
        ("""Extracts nth percentile from omnet vec files and appends it to the corresponding
scalar file."""),
        formatter_class=argparse.ArgumentDefaultsHelpFormatter)
parser.add_argument('files', metavar='files', type=str, nargs='+',
        help="Name of the vec files to export percentiles from.")
parser.add_argument(
        "-p", "--percentile", type=int, default=90,
        help="Percentile to extract.")
args = parser.parse_args()

for vec_file in args.files:
    sca_file = vec_file[:-3]+"sca"
    vectors = {}

    print(f"Parsing file {vec_file}...")

    with open(vec_file, 'r') as fin:
        line = fin.readline()
        while line:
            splitted_line = line.split()

            if len(splitted_line) > 0:
                if not splitted_line[0].isnumeric():
                    if splitted_line[0] == "vector":
                        vector = {}
                        idx = int(splitted_line[1])
                        vector["module"] = splitted_line[2]
                        vector["name"] = splitted_line[3].split(":")[0]
                        vector["values"] = []
                        vectors[idx] = vector
                else:
                    idx = int(splitted_line[0])
                    val = float(splitted_line[3])
                    vectors[idx]["values"].append(val)

            line = fin.readline()
    
    print(f"Found {len(vectors)} vectors.")
    print(f"Calculating {args.percentile}th-percentiles...")

    for idx, vector in vectors.items():
        if len(vector['values']) > 0:
            vector["percentile"] = np.percentile(np.array(vector["values"]), args.percentile)
        else:
            vector["percentile"] = 0

        print(f"{vector['module']}.{vector['name']}: {len(vector['values'])} values, {vector['percentile']}")

    print("Writing percentiles to scalar file...")
    
    with open(sca_file, 'a') as fout:
        for idx, vector in vectors.items():
            fout.write(f"scalar {vector['module']} {vector['name']}:{args.percentile}percentile {vector['percentile']}\n")
            fout.write(f"attr source {vector['name']}\n")
            fout.write(f"attr title \"{vector['name']}, {args.percentile}percentile\"\n")