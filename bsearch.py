#!/usr/bin/env python
test_list = [1,5,7,9,11,16,24,53,67,88,99,105]

def bsearch(lst, v, low=0, high=None):
    if high == None:
        high = len(lst) - 1
        
    if high < low:
        return False
        
    mid = (low + high) // 2
    
    if lst[mid] > v:
        return bsearch(lst, v, low, mid-1)
    elif lst[mid] < v:
        return bsearch(lst, v, mid+1, high)
    else:
        return mid

print bsearch(test_list, 1)
print bsearch(test_list, 9)
print bsearch(test_list, 99)
print bsearch(test_list, 18)
print bsearch(test_list, 0)
print bsearch(test_list, 106)
