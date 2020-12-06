#!/usr/bin/env python3.7

import os
import signal
import sys
import math
import subprocess
from argparse import ArgumentParser

import libtropicity as tr


def parseCommandline():
    parser = ArgumentParser(prog="tropicity.py", description="nothing yet", add_help=True)
    parser.add_argument("--input", help=" ", dest="inputfile", action="store", type=str, required=True)
    argparse = parser.parse_args()
    return argparse


def main():
    # signal.signal(signal.SIGINT, signal_handler)
    args = parseCommandline()
    print(args)
    C = tr.cube(args.inputfile)

    tropplane = C.gettropplaneZ(7.0)
    filename = "new-tropicities.txt"
    C.writetropplaneZ(filename, tropplane)


if __name__ == "__main__":
    main()

