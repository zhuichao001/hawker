#!/usr/bin/python
# -*- coding: UTF-8 -*-


#给定一个升序数组，给出和为sum的两个数的index


def indexOfSum(items, val):
    i, j = 0, len(items)-1
    while i<j:
        if items[i]+items[j] < val:
            i += 1
        elif items[i]+items[j] > val:
            j -= 1
        else:
            return (i, j)
    return None


if __name__ == '__main__':
    print indexOfSum([2,3,5,6,8], 9)
    print indexOfSum([2,3,5,6,8], 4)
