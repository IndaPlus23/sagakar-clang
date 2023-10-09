#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    long long term1, term2;
    while (scanf("%lld%lld", &term1, &term2) == 2) {
        printf("%lld\n", llabs(term1 - term2));
    }
    return 0;
}