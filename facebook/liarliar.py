import sys


def main():
    filename = sys.argv[1]
    
    bp_graph = { 'a': {}, 'b': {} }

    f = open(filename, 'r')
    members = int(f.readline().strip())
    for n in range(members):
        line = f.readline().strip()
        accuser, num_accusees = tuple(s.strip() for s in line.split())
        num_accusees = int(num_accusees)
        for i in range(num_accusees):
            inner_line = f.readline().strip()
            accusee = inner_line.strip()
            if accuser in bp_graph['a']:
                bp_graph['a'][accusee] = not bp_graph['a'][accuser]
                bp_graph['b'][accusee] = bp_graph['a'][accuser]
            elif accuser in bp_graph['b']:
                bp_graph['b'][accusee] = not bp_graph['b'][accuser]
                bp_graph['a'][accusee] = bp_graph['a'][accuser]
            else:
                bp_graph['a'][accuser] = True
                bp_graph['a'][accusee] = False
                bp_graph['b'][accuser] = False
                bp_graph['b'][accusee] = True
    
    f.close()
    
    totals = []
    for label, partition in bp_graph.iteritems():
        total = 0
        for person, truth in partition.iteritems():
            total += (1 if truth else 0)
        totals.append(total)
    totals.reverse()
    
    for t in totals:
        print t,
    
    return 0


if __name__ == '__main__':
    sys.exit(main())
