#!/usr/bin/env python
import sys


def bottoms_up(t):
    """determine the largest sum of all possible paths 
    through a tree.
    
    start from the bottom row and work up reducing the
    complexity of the problem."""
    while len(t) > 1:
        last_row = t[-1]
        for i in xrange(len(last_row) - 1):
            # add the largest value of the children in 
            # the last row to the parent in the next row up
            t[-2][i] += max(last_row[i:i+2])
        
        del t[-1]
    
    return t[0][0]


def yodle():
    f = open('triangle.txt', 'r')
    
    # build the tree as a list of lists
    tree = [[int(x) for x in line.strip().split(' ')] for line in f]
    
    print bottoms_up(tree)
    
    f.close()
    
    return 0


if __name__ == '__main__':
    sys.exit(yodle())
