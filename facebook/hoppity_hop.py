import sys


def main():
    filename = sys.argv[1]
    
    f = open(filename, 'r')
    number = int(f.read().strip())
    
    for i in range(number):
        val = i + 1
        if ((val % 3) == 0) and ((val % 5) == 0):
            print "Hop"
        elif ((val % 3) == 0):
            print "Hoppity"
        elif ((val % 5) == 0):
            print "Hophop"
    
    f.close()
    
    return 0


if __name__ == '__main__':
    sys.exit(main())
