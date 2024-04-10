import math


def main():
    n = int(input())
    customers = list(map(int, input().split()))
    head, team = map(int, input().split())

    ans = 0
    for customer in customers:
        ans += 1
        customer -= head
        if customer > 0:
            ans += math.ceil(customer/team)

    print(ans)

    
main()