def solve_greedy(numbers, target):
    numbers.sort(reverse=True)
    r = target
    res = [target]

    i = 0
    while i < len(numbers):
        if r % numbers[i] == 0:
            r //= numbers[i]
            res.append(r)
            
            if r == 1:
                return reversed(res)

            continue
        i += 1

    return [-1]

n = int(input().split()[0])
nums = list(map(int, input().split()))

print(*solve_greedy(nums, n))
