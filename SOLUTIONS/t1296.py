import sys

for line in sys.stdin:
    n = int(line.strip())
    array = [int(input().strip()) for _ in range(n)]

    maxx = 0
    sum_ = 0
    for i in range(n):
        sum_ += array[i]
        if sum_ <= 0:
            sum_ = 0
        if sum_ > maxx:
            maxx = sum_

    print(maxx)
