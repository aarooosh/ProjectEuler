def check(i, m, digits, memo):
    if i == 0 and len(m) == 0:
        return True
    if len(m) == 0 or i < 0:
        return False
    if (i, m) in memo:
        return memo[(i, m)]
    for j in range(1, digits + 1):
        num = int(m[:j])
        if check(i - num, m[j:], digits, memo):
            memo[(i, m)] = True
            return True
    memo[(i, m)] = False
    return False

def compute_sum():
    total_sum = 0
    
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
