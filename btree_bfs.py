class Node(object):
    value = None
    left = None
    right = None
    
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right

root = Node(0, Node(1, Node(3), Node(4)), Node(2, None, Node(5)))

def breadth_first_search(node):
    queue = [node]
    while len(queue):
        next_queue = []
        for n in queue:
            print n.value,
            if n.left:
                next_queue.append(n.left)
            if n.right:
                next_queue.append(n.right)
        print
        queue = next_queue

if __name__ == '__main__':
    breadth_first_search(root)
