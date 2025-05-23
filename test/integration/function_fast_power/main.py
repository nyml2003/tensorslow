def fast_power(base, exponent):
    result = 1
    current_power = base

    while exponent > 0:
        # 如果当前指数是奇数
        if exponent % 2 == 1:
            result *= current_power

        # 将指数减半
        exponent //= 2
        # 更新当前幂次
        current_power **= 2

    return result


print(fast_power(2, 10))  # 输出 1024
print(fast_power(3, 13))  # 输出 1594323
