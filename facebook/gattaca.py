import sys
import math


def main():
    filename = sys.argv[1]
    
    intervals = []
    
    sequence = ''
    f = open(filename, 'r')
    sequence_size = int(f.readline().strip())
    for i in range(int(math.ceil(sequence_size / 80.0))):
        sequence += f.readline().strip()
    
    num_intervals = int(f.readline().strip())
    for i in range(num_intervals):
        line = f.readline().strip()
        intervals.append(tuple(int(c) for c in line.split() if len(c)))
    
    f.close()
    
    intervals.sort(cmp=lambda x,y: cmp(x[1], y[1]))
    
    compatible = dict((i, -1) for i in range(num_intervals))
    for i in range(num_intervals):
        for c in sorted(range(i), reverse=True):
            if intervals[c][1] < intervals[i][0]:
                compatible[i] = c
                break
    
    profits = [0]
    for i in range(1, num_intervals):
        profit_in = intervals[i - 1][2] + profits[compatible[i - 1] + 1]
        profit_ex = profits[i - 1]
        profits.append(max(profit_in, profit_ex))
    
    print profits[-1]
    
    return 0


if __name__ == '__main__':
    sys.exit(main())
