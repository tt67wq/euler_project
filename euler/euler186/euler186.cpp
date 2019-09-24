#include <iostream>

static int sk[55];
struct {
        int group, next, last, size;
} packs[1000000];

static void init() {
        for (int k = 1; k <= 55; k++)
                sk[k - 1] = (100003 - 200003 * k + 300007LL * k * k * k) % 1000000;
        for (int i = 0; i < 1000000; i++) {
                packs[i].group = packs[i].last = i;
                packs[i].next = -1;
                packs[i].size = 1;
        }
}

static int next_sk() {
        static int skidx = 0;
        int res = sk[skidx];
        sk[skidx] = (res + sk[(skidx + 31) % 55]) % 1000000;
        skidx = (skidx + 1) % 55;
        return res;
}

static void merge_into(int g1, int g2) {
        if (packs[g1].size < packs[g2].size)
                std::swap(g1, g2);
        packs[packs[g1].last].next = g2;
        packs[g1].last = packs[g2].last;
        packs[g1].size += packs[g2].size;
        for (int n = g2; n != -1; n = packs[n].next) {
                packs[n].group = g1;
        }
}

static int round() {
        int n1 = next_sk();
        int n2 = next_sk();
        if (n1 == n2)
                return 0;
        int g1 = packs[n1].group;
        int g2 = packs[n2].group;
        if (g1 != g2)
                merge_into(g1, g2);
        return 1;
}

int main() {
        init();
        int i = 0;
        while (packs[packs[524287].group].size < 990000) {
                i += round();
        };
        std::cout << "Solution: " << i << std::endl;
        return 0;
}
