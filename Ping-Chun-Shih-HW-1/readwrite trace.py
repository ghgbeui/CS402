# -*- coding: utf-8 -*-
"""
Created on Sun Jan 28 23:43:20 2024

@author: kevin
"""

def read_trace_file(filename):
    reads = []
    writes = []
    with open(filename, 'r') as file:
        for line in file:
            parts = line.strip().split()
            if len(parts) == 2:
                operation_type = int(parts[0])
                address = int(parts[1], 16)  # Convert hexadecimal address to decimal
                if operation_type == 0:
                    reads.append(address)
                elif operation_type == 1:
                    writes.append(address)
    return reads, writes

if __name__ == "__main__":
    cc1_reads, cc1_writes = read_trace_file('c:/cc1.dat')
    spice_reads, spice_writes = read_trace_file('c:/spice.dat')

    print("CC1 Trace:")
    print("Reads:", len(cc1_reads))
    print("Writes:", len(cc1_writes))
    print()
    print("Spice Trace:")
    print("Reads:", len(spice_reads))
    print("Writes:", len(spice_writes))
