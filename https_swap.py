#!/usr/bin/env python3

"""
    https_swap -- swaps a list of http URLs with https.
    Copyright (C) 2020  Brenden Davidson

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
"""

from sys import argv, stderr
import re

def replace_protocol(filename):
    """
        Replaces instances of 'http://' with 'https://'

        Arguments:

            filename -- name of file to read from
    """

    new_filename = "https_" + str(filename)

    out_file = open(new_filename, "w+")

    with open(filename, "r") as in_file:
        line = in_file.readline().strip()
        while line != "":
            line = line.replace(" ", "")
            line = line.replace("\r", "")
            line = line.replace("\n", "")
            line = line.replace("\t", "")
            line = line.replace("http", "https")
            if line != "" or line != "\n":
                out_file.write(line + "\n")
            line = in_file.readline()

    out_file.close()


if __name__ == "__main__":
    if len(argv) != 2:
        print("Please provide an input file.", file=stderr)
        exit(1)

    replace_protocol(argv[1])