import matplotlib.pyplot as plt
import numpy as np

def read_trace_file(filename):
    """
    Reads a trace file and extracts addresses for instruction fetches.

    Args:
        filename (str): The path to the trace file.

    Returns:
        list: A list of decimal addresses extracted from the trace file.
    """
    addresses = []
    with open(filename, 'r') as file:
        for line in file:
            parts = line.strip().split()
            if len(parts) == 2 and parts[0] == '2':  # Check for instruction fetches
                addresses.append(int(parts[1], 16))  # Convert hexadecimal address to decimal
    return addresses

def plot_histogram(addresses, title):
    """
    Plots a histogram of address distribution.

    Args:
        addresses (list): A list of decimal addresses.
        title (str): The title of the histogram.
    """
    # Count occurrences of each address
    address_counts = np.bincount(addresses)

    # Find non-zero addresses
    non_zero_addresses = np.nonzero(address_counts)[0]
    print("Non-zero addresses:", non_zero_addresses)

    # Select a subset of addresses with non-zero occurrences
    max_addresses = 500  # Maximum number of addresses to plot
    selected_addresses = non_zero_addresses[:max_addresses]
    selected_counts = address_counts[selected_addresses]
    print("Selected addresses:", selected_addresses)
    print("Selected counts:", selected_counts)

    # Plot histogram
    plt.figure(figsize=(10, 6))
    plt.hist(addresses, bins=100)  # Adjust the number of bins as needed
    plt.title(title)
    plt.xlabel('Address (Decimal)')
    plt.ylabel('Occurrences')
    plt.grid(True)
    plt.show()



if __name__ == "__main__":
    # Read trace files and plot histograms
    cc1_addresses = read_trace_file('c:/cc1.dat')
    spice_addresses = read_trace_file('c:/spice.dat')

    # Plot histogram for cc1.din
    plot_histogram(cc1_addresses, 'Histogram of Address Distribution for cc1.din')

    # Plot histogram for spice.din
    plot_histogram(spice_addresses, 'Histogram of Address Distribution for spice.din')










