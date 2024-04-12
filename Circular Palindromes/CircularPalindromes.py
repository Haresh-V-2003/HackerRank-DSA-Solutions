#!/bin/python3

import os
import sys
import random
import bisect

#
# Complete the circularPalindromes function below.
#
def get_len(s, ll, flag):
    # use flag = 0 for odd number of letters in palindrome, 1 for even
    maxlen = 1
    l1 = ll - 2
    l2 = ll + 1 + flag
    while l1>=0 and l2 < len(s) and s[l1] == s[l2]:
        maxlen += 1
        l1 -= 1
        l2 += 1
    return 2*maxlen + flag

def max_pal(s):
    # find the length of the longest palindrome in s
    ls = len(s)
    maxlen = 1 
    for ll in range(1, ls):
        if s[ll-1] == s[ll]:
            newlen = get_len(s, ll, 0)
            if newlen > maxlen:
                maxlen = newlen
    for ll in range(1, ls-1):
        if s[ll-1] == s[ll+1]:
            newlen = get_len(s, ll, 1)
            if newlen > maxlen:
                maxlen = newlen
    return maxlen

def get_len_round_fast(slist, ll, lens):
    ls = len(slist)
    if ls == 1:
        return (slist[0][1], slist[0][2])
    start = slist[ll][1]
    end = slist[ll][2]
    l1 = ll - 1
    l2 = ll + 1
    notdone = True
    while notdone and (end - start)<lens and slist[l1 % ls][0] == slist[l2 % ls][0]:
        lgth1 = slist[l1][2]-slist[l1][1]
        if lgth1 < 0:
            lgth1 += lens
        ls2 = l2 % ls
        lgth2 = slist[ls2][2]-slist[ls2][1]
        if lgth2 < 0:
            lgth2 += lens
        lmax = lens - (end-start)
        if lgth1 != lgth2:
            notdone = False
        # make lgth2 the smaller for subsequent calculations
        if lgth1 < lgth2:
            lgth2 = lgth1
        if lgth2 + lgth2 > lmax:
            lgth2 = lmax//2
            notdone = False
        end+= lgth2
        start -= lgth2
        l1 -= 1
        l2 += 1
#        print(l1, l2)
    return (start, end)
    
def compress_string(s):
    # replaces strings of contiguous identical characters with (char, #) pairs
    #   where # is the end of the string sequence
    ls = []
    cc = '.'
    start = 0
    for ss in range(len(s)):    
        if s[ss] != cc: # new char
            ls.append((cc, start, ss))
            start = ss
            cc = s[ss]
    ls.append((cc, start, len(s))) # append the last characters encountered
    ls.pop(0) # first value is a throwaway one
    if ls[0][0] == ls[-1][0]: # stitch the ends, move the start of sequence before 0
        ls[0] = (ls[0][0], ls[-1][1]-len(s), ls[0][2])
        ls.pop() # remove last element, now that it is combined with the first
    return ls

        
def make_pal_dict(slist, lens):
    ls = len(slist)
    dict1 = {}
    list1 = []
    for ll in range(ls):
        (start, stop) = get_len_round_fast(slist, ll, lens)
#        print(ll, start, stop)
        lgth = stop - start
        if lgth > 1:
            if start < 0:
                start, stop = start+lens, stop+lens
            if lgth in dict1:
                dict1[lgth].append((start, stop))
            else:
                dict1[lgth]= [(start, stop)]
                bisect.insort(list1, lgth)
    for (_, start, stop) in slist:
        lgth = stop - start
        if lgth > 1:
            if start < 0:
                start, stop = start+lens, stop+lens
            if lgth in dict1:
                if (start, stop) in dict1[lgth]:
                    dict1[lgth].remove((start, stop))
                dict1[lgth].append((-start, -stop))
            else:
                dict1[lgth]= [(-start, -stop)]
                bisect.insort(list1, lgth)        
    return (dict1, list1)

        
def cp(s):
    ls = len(s)
    slist = compress_string(s)
#    print(slist)
    (dict1, list1) = make_pal_dict(slist, ls)
#    print(dict1, list1)
    maxes = [] # value for k = 0
    ll = len(list1)-1 # start here to look for longest palindrome 
    for k in range(ls):
        maxlgth = 1 
        done = False
        ks = k + ls
        for ind in range(ll, -1, -1): # go backwards through list of lengths
            if done: # max value already reached for a longer word
                break
            lgth = list1[ind]
            if lgth < maxlgth: # only shorter words available past here
                break
            for (start, stop) in dict1[lgth]:
                if start<=0 and stop <= 0: # same chars, no need to cut palindrome at both ends
#                    print(start, stop, k)
                    if -start <= k < -stop:
                        lgth1 = max(-stop - k, k+start) 
                    else:
                        lgth1 = lgth
                    if -start < ks <= -stop:
                        lgth2 = max(ks + start, -stop - ks)
                    else:
                        lgth2 = lgth
                    #print(lgth1, lgth2)
                else:
#                print(lgth, maxlgth, k, start, stop)
                    if start <= k <= stop:
                        lgth1 = abs(start+stop-k-k)
                    else:
                        lgth1 = lgth
                    if start <= ks <= stop:
                        lgth2 = abs(start+stop-ks-ks)
                    else:
                        lgth2 = lgth
                if lgth1 > lgth2:
                    lgth1 = lgth2
                if maxlgth < lgth1:
                    maxlgth = lgth1
#                    print(maxlgth)
                if lgth1 == lgth:
                    done = True
                    break
#        print("k=", k, "ml=", maxlgth)
        maxes.append(maxlgth)
    return maxes

def circularPalindromes(s):
    #
    # Write your code here.
    #
    debug = 0
    if debug == 0:
        return cp(s)
    elif debug == 1:
        for ii in range(1000):
            s = ""
            for jj in range(10):
                s += chr(97 + random.randrange(0, 26))
            r1 = cp(s) 
            r = cp_gold(s)
            if r1 != r:
                print(r1, "should be", r, "for", s)
        return [1, 1, 1]
    elif debug == 2:
        return cp_gold(s)
    else:
        (dict1, list1) = make_pal_list(s)
        print(dict1, list1)
        return cp_gold(s)
                
    
def rotate_s(s, val):
    val = val % len(s)
    return s[val:]+s[:val]
    
def cp_gold(s):
    #
    # Write your code here.
    #
    ls = len(s)
    maxes = [max_pal(s)]
    for ll in range(1, ls):
        s = rotate_s(s, 1)
        maxes.append(max_pal(s))
    return maxes

    
if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input())

    s = input()

    result = circularPalindromes(s)

    fptr.write('\n'.join(map(str, result)))
    fptr.write('\n')

    fptr.close()
