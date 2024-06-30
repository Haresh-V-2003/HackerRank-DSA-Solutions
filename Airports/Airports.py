import math
import os
import random
import re
import sys
from heapq import heappop, heappush, heapify

#
# Complete the 'airports' function below.
#
# The function is expected to return an INTEGER_ARRAY.
# The function accepts following parameters:
#  1. INTEGER d
#  2. INTEGER_ARRAY x
#


def airports(min_dist, airports):
    road = sorted(set(airports))
    len_road = len(road)
    answers = []
    airport_indices = dict()
    for i, a in enumerate(road):
        airport_indices[a] = i    
    qty = [0] * len_road
    for a in airports:
        qty[airport_indices[a]] += 1
    safe = []
    near_left = []
    near_right = []
    near_both = []
    for i in range(len_road - 1):
        gap = (i, i + 1)
        safe.append(gap)
    heapify(near_left)
    heapify(near_right)
    heapify(near_both)
    left_airport = 0
    right_airport = len_road - 1
    second_left = 1
    second_right = len_road - 2
    next_airport = list(range(1, len_road)) + ['N']
    prev_airport = ['N'] + list(range(len_road - 1))
    for ap in reversed(airports):
        road_left_airport, road_right_airport = road[left_airport], road[right_airport]
        while safe and (road[safe[-1][1]] - road_left_airport < min_dist or road_right_airport - road[safe[-1][0]] < min_dist):
            gap = safe.pop()
            if road[gap[1]] - road_left_airport < min_dist:
                heappush(near_left,(0 - road[gap[1]],gap))
            else:
                heappush(near_right,(road[gap[0]],gap))
        while near_left and road_right_airport - road[near_left[0][1][0]] < min_dist:
            gap = heappop(near_left)[1]
            heappush(near_both,(road[gap[0]] - road[gap[1]], gap))
        while near_right and road[near_right[0][1][1]] - road_left_airport < min_dist:
            gap = heappop(near_right)[1]
            heappush(near_both,(road[gap[0]] - road[gap[1]], gap))
        while near_both and (near_both[0][1][0] < left_airport or near_both[0][1][1] > right_airport):
            heappop(near_both)
        if safe:
            answers.append(0)
        else:
            possible_answers = [min_dist]
            if left_airport != right_airport:
                if qty[left_airport] == 1:
                    possible_answers.append(min_dist + road_left_airport - road[second_left])
                if qty[right_airport] == 1:
                    possible_answers.append(min_dist + road[second_right] - road_right_airport)
            if near_left:
                possible_answers.append(max(0, min_dist + road_left_airport - road[near_left[0][1][1]]))
            if near_right:
                possible_answers.append(max(0, min_dist + road[near_right[0][1][0]] - road_right_airport))
            if near_both:
                possible_answers.append(0)
                nb = near_both[0][1]
                possible_answers[-1] += max(0,min_dist + road_left_airport - road[nb[1]])
                possible_answers[-1] += max(0,min_dist + road[nb[0]] - road_right_airport)
            answers.append(min(possible_answers))
        ai = airport_indices[ap]
        qty[ai] -= 1
        if qty[ai]:
            continue
        while second_left < len_road - 1 and qty[second_left] == 0:
            second_left += 1
        while second_right > 0 and qty[second_right] == 0:
            second_right -= 1  
        if ai == left_airport or ai == right_airport:
            while left_airport < len_road - 1 and qty[left_airport] == 0:
                left_airport += 1
            while right_airport > 0 and qty[right_airport] == 0:
                right_airport -= 1
            second_left = max(second_left, left_airport + 1)
            second_right = min(second_right, right_airport - 1)
            while second_left < len_road - 1 and qty[second_left] == 0:
                second_left += 1
            while second_right > 0 and qty[second_right] == 0:
                second_right -= 1   
        else:
            l = prev_airport[ai]
            r = next_airport[ai]
            next_airport[l] = r
            prev_airport[r] = l
            gap = (l, r)
            safe.append(gap)    
    answers.reverse()
    answers[0] = 0
    return answers

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')
    q = int(input().strip())
    for q_itr in range(q):
        first_multiple_input = input().rstrip().split()
        n = int(first_multiple_input[0])
        d = int(first_multiple_input[1])
        x = list(map(int, input().rstrip().split()))
        result = airports(d, x)
        fptr.write(' '.join(map(str, result)))
        fptr.write('\n')
    fptr.close()
