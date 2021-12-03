from guppy import hpy

with open("../../data/cleaned-shakespeare.txt") as f:
    for line in f:
        # its somehow more memory efficient to split twice instead of storing in variable - 13mb vs 60 mb
        # also faster - 500ms vs 900 ms
        print(f"Total words:    {len(line.split(' '))}")
        s = set(line.split(' '))
        print(f"Distinct words: {len(s)}\n")

print("Memory usage:")
h = hpy()
print(h.heap())
