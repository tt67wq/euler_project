#include <stdio.h>
#include <time.h>

typedef struct rr {
        int p, q;
} rr;

enum { MAX_STACK = 50000000, FRAC = 100, MAX_DENOM = 100000000 };

int stack_hw = 0;
rr stack[MAX_STACK];
int last = 0;
void push(int p, int q) {
        stack[last].p = p;
        stack[last].q = q;
        if (last > stack_hw)
                stack_hw = last;
        ++last;
}
void pop() { --last; }
rr *front() { return stack + last - 1; }
int empty() { return 0 == last; }

int main() {
        rr *f;
        long n = 0, m = 1, N = 1, M = FRAC / 2, m_, n_;
        long p, q, cnt = 0;
        double start = clock();

        push(N, M);
        while (!empty()) {
                f = front();
                N = f->p;
                M = f->q;
                n_ = n + N;
                m_ = m + M;
                p = n * M + N * m;
                q = 2 * m * M;
                if (q <= MAX_DENOM) {
                        push(n_, m_);
                        if (FRAC * p < q)
                                ++cnt;
                        continue;
                }
                n = N;
                m = M;
                pop();
        }

        printf("got %ld in %.3gs (stack high watermark = %d)\n", cnt, (clock() - start) / CLOCKS_PER_SEC, stack_hw);
        return 0;
}
