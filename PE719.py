def check(sum, m, digits, memo):
    # Recursively Makes Partitions of the string , without exceeding the max digit size
    # Currently this is the slowest step and could use some optimizations
    if sum == 0 and len(m) == 0:
        # Sum is zero and all digits used
        return True
    if len(m) == 0 or sum < 0:
        # prematurely used up all digits  or sum < 0
        return False
    if (sum, m) in memo:
        # Checks if the combo is already present in our memory
        return memo[(sum, m)]
    for j in range(1, digits + 1):
        num = int(m[:j])
        if check(sum - num, m[j:], digits, memo):
            # checks if sum-num can be represented , because then adding num makes sum representable
            memo[(sum, m)] = True
            return True
    memo[(sum, m)] = False
    return False

def compute_sum():
    total_sum = 0
    # Going over only the first 10^6 elements and using their squares 
    for i in range(2, 10000001):
        num = i + k
        squared = num ** 2
        str_squared = str(squared)
        digits = (len(str_squared) + 1) // 2
        memo = {}
        if check(num, str_squared, digits, memo):
            total_sum += squared
    print('sum =', total_sum)

compute_sum()
# Unfortunately this code takes about 3 hours to run :(
