import random

def generate_addresses(num_addresses, cache_size, num_columns):
    block_size = 64  # Block size in bytes
    cache_size_bytes = cache_size * 1024  # Convert cache size to bytes
    num_sets = cache_size_bytes // (block_size * num_columns)
    index_bits = num_sets.bit_length() - 1
    tag_bits = 32 - index_bits - 6  # 6 bits for block offset

    addresses = []
    for _ in range(num_addresses):
        tag = random.randint(0, (1 << tag_bits) - 1)
        index = random.randint(0, (1 << index_bits) - 1)
        block_offset = random.randint(0, (1 << 6) - 1)
        address = (tag << (index_bits + 6)) | (index << 6) | block_offset
        addresses.append(address)
    return addresses

def address_to_binary(address):
    binary_address = bin(address)[2:].zfill(32)
    return binary_address

# Get user input for cache size in kB and number of columns
cache_size_kb = int(input("Enter the cache size in kilobytes (kB): "))
num_columns = int(input("Enter the number of columns (associativity): "))

# Get user input for the number of addresses to generate
num_addresses = int(input("Enter the number of addresses to generate: "))

# Generate random addresses based on user input
addresses = generate_addresses(num_addresses, cache_size_kb, num_columns)

# Convert addresses to binary representation
binary_addresses = [address_to_binary(address) for address in addresses]

# Write addresses to a file in binary format
filename = "SampleInput.txt"
with open(filename, "w") as file:
    for address in binary_addresses:
        file.write(address + "\n")

print(f"{num_addresses} addresses have been written to {filename} in binary format.")
