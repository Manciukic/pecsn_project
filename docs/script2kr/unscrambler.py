import sys

def get_bit(i, n):
    return (n>>i)%2

def conversion(n, k=4):
    s = 0
    for i in range(k):
        if not get_bit(i, n):
            s += 2**(k-i-1)
    print(f"{n} becomes {s} (k={k})")
    return s

def print_usage():
    print("Usage: ./unscrambler.py in.txt out.txt [k]")

def main():
    if len(sys.argv) < 3:
        print_usage()
        sys.exit(1)

    if len(sys.argv) == 4:
        k = int(sys.argv[3])
    else:
        k = 4
    
    with open(sys.argv[1], 'r') as f:
        lines = f.readlines()
    
    out_dict_lines = {conversion(i, k):l for i,l in enumerate(lines)}
    out_lines = [out_dict_lines[i] for i in sorted(out_dict_lines.keys())]

    with open(sys.argv[2], 'w') as f:
        f.writelines(out_lines)

if __name__ == "__main__":
    main()
