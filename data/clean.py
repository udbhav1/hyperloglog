import string

with open("shakespeare.txt") as f:
    cleaned = []
    for line in f:
        line = line.strip()
        # exclude stanza numbers and years
        if line and not line.isdigit():
            line = line.split()
            for word in line:
                # remove punctuation from edges
                w = word.strip(string.punctuation)
                if w:
                    # lowercase for accuracy
                    cleaned.append(w.lower())
    out = open("cleaned-shakespeare.txt", "w")
    out.write(" ".join(cleaned))
    out.close()
