#!/usr/bin/env python3

""" Script to run analysis on omnet results.

I was too lazy and I've used only bash commands.
I didn't write a shell script since I wanted to use a more advanced 
argument parser.
To execute this on Windows, I think you need either LSW or MinGW.
Make sure that omnet bin folder is in your PATH.
"""

import sys
import argparse
import os

# Path of required scripts
path = os.path.dirname(sys.argv[0])
parser_exec = f"{path}/parser"
log_exec = f"{path}/log_file.py"
unscrambler_exec = f"{path}/unscrambler.py"
factorial_exec = f"{path}/factorial2kr.py"

scavetool_tmp_file = "tmp.csv"
grep_tmp_file = "tmp2.csv"
parser_tmp_file = "tmp.out"
log_tmp_file = "tmp_log.out"
unscrambled_file = "tmp_unscr.out"

parser = argparse.ArgumentParser(
        ("""2kr analysis of omnet output
Example:
./analyze.py --config FactorialAnalysisFifo 
        --directory ../../simulations/results \\
        --module Network.kitchen \\
        --scalar fifoQueueLength:timeavg \\
        --log \\
        --confidence 0.9 \\
        --residuals residuals \\
        --qqnorm qqnorm \\
        --plot \\
        
This command finds the runs of FactorialAnalysisFifo within the defined folder,
extracts scalars regarding the queue length of the kitchen and feeds it to the 
parser. The resulting metrics are log-transformed and the row order is corrected
(through the unscramble script). The analysis is run with the given confidence
and residuals and qqnorm files are written to the provided ones. Finally, gnuplot
is use to plot residuals and qqnorm.
"""),
        formatter_class=argparse.ArgumentDefaultsHelpFormatter)
parser.add_argument(
        "-c", "--config", type=str, required=True,
        help="Name of the configuration to export data from. (mandatory)")
parser.add_argument(
        "-d", "--directory", type=str, required=True,
        help="Directory where omnet result files are stored. (mandatory)")
parser.add_argument(
        "-m", "--module", type=str, default="", required=True,
        help="Omnet module to extract the scalar metric from. (mandatory)")
parser.add_argument(
        "-s", "--scalar", type=str, default="", required=True,
        help="Omnet scalar to extract. (mandatory)")
parser.add_argument(
        "--log", action="store_true", default=False,
        help="Apply log on all scalars before analysis.")
parser.add_argument(
        "--plot", action="store_true", default=False,
        help="Show residuals and qqplot.")
parser.add_argument(
        "--confidence", type=float, default=0.9,
        help="Confidence level")
parser.add_argument(
        "--residuals", type=str, default='residuals',
        help=("Name of the file where to save the scatter plot of residuals. "
              "Ignore trend if the magnitude of residuals is smaller than 1/10 "
              "of the magnitude of responses. If the trend goes up or down "
              "then there are other factors or side effects that are not "
              "accounted by the current analysis."))
parser.add_argument(
        "--qqnorm", type=str, default='qqnorm',
        help=("Name of the file where to save the normal Q-Q plot of errors. "
              "The analysis is statistically significant if the plot is "
              "approximately linear."))
args = parser.parse_args()

print("Extracting...")
os.system(f"scavetool x {args.directory}/{args.config}*.sca -o {scavetool_tmp_file}")

print("Filtering rows...")
os.system(f"echo > {grep_tmp_file}")
os.system(f"grep scalar {scavetool_tmp_file} | grep {args.module} | grep {args.scalar} >> {grep_tmp_file}")

print("Parsing...")
os.system(f"{parser_exec} {grep_tmp_file} {parser_tmp_file}")

if args.log:
    print("Log...")
    os.system(f"{log_exec} {parser_tmp_file} {log_tmp_file}")
    analysis_infile = log_tmp_file
else:
    analysis_infile = parser_tmp_file

print("Unscrambling...")
os.system(f"{unscrambler_exec} {analysis_infile} {unscrambled_file}")

print("Analyzing...")
os.system(f"{factorial_exec} --confidence {args.confidence} --residuals {args.residuals} --qqnorm {args.qqnorm} {analysis_infile}")

print("Removing tmp files...")
os.system(f"rm {scavetool_tmp_file} {grep_tmp_file} {parser_tmp_file} {log_tmp_file if args.log else ''} {unscrambled_file}")

if args.plot:
    print("Plotting...")
    os.system(f"gnuplot -e \"plot '{args.qqnorm}'\" -p &")
    os.system(f"gnuplot -e \"plot '{args.residuals}'\" -p &")
