#include <cmath>
#include <iostream>
#include <vector>

std::vector<bool> sieve;

bool isPrime(unsigned int x) {
        if ((x & 1) == 0)
                return x == 2;

        return sieve[x >> 1];
}

void fillSieve(unsigned int size) {
        const unsigned int half = (size >> 1) + 1;
        sieve.resize(half, true);
        sieve[0] = false;

        for (unsigned int i = 1; 2 * i * i < half; i++) {
                if (sieve[i]) {
                        unsigned int current = 3 * i + 1;
                        while (current < half) {
                                sieve[current] = false;
                                current += 2 * i + 1;
                        }
                }
        }
}

template <typename T> T gcd(T a, T b) {
        while (a != 0) {
                T c = a;
                a = b % a;
                b = c;
        }
        return b;
}

unsigned long long count(unsigned int limit) {
        unsigned long long sum = 0;

        for (unsigned int x = 2; x * x < limit; x++) {
                for (unsigned int k = 1; k * x * x < limit; k++) {
                        auto a = k * x * x - 1;
                        if (!isPrime(a))
                                continue;
                        for (unsigned int y = 1; y < x; y++) {
                                if ((x & 1) == 0 && (y & 1) == 0)
                                        y++;
                                auto b = k * x * y - 1;
                                auto c = k * y * y - 1;

                                if (!isPrime(b))
                                        continue;
                                if (!isPrime(c))
                                        continue;

                                if (gcd(x, y) > 1)
                                        continue;

                                sum += a + b + c;
                        }
                }
        }
        return sum;
}

int main() {
        unsigned int limit = 100000000;
        std::cin >> limit;

        fillSieve(limit);

        std::cout << count(limit) << std::endl;
        return 0;
}