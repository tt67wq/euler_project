// 以下為C++ 程式碼，在G++ 下編譯通過

// 僅用於示範如何根據權值建構霍夫曼樹，

// 沒有經過性能上的優化及加上完善的異常處理。

#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>

using namespace std;

const int size = 10;

struct node {         // 霍夫曼樹節點結構
        unsigned key; // 保存權值
        node *lchild; // 左孩子指針
        node *rchild; // 右孩子指針
};

deque<node *> forest;
deque<bool> code; // 此處也可使用bitset
node *ptr;

int frequency[size] = {0};
void printCode(deque<bool> ptr); // 用於輸出霍夫曼編碼
bool compare(node *a, node *b) { return a->key < b->key; }

int main(int argc, char *argv[]) {
        for (int i = 0; i < size; i++) {
                cin >> frequency[i]; // 輸入10個權值
                ptr = new node;
                ptr->key = frequency[i];
                ptr->lchild = NULL;
                ptr->rchild = NULL;
                forest.push_back(ptr);

        } // 形成森林，森林中的每一棵樹都是一個節點

        // 從森林構建霍夫曼樹
        for (int i = 0; i < size - 1; i++) {
                sort(forest.begin(), forest.end(), compare);
                ptr = new node;

                // 以下代碼使用下標索引隊列元素，具有潛在危險，使用時請注意
                ptr->key = forest[0]->key + forest[1]->key;
                ptr->lchild = forest[0];
                ptr->rchild = forest[1];
                forest.pop_front();
                forest.pop_front();
                forest.push_back(ptr);
        }

        ptr = forest.front(); // ptr是一個指向根的指針

        // system("PAUSE");
        return EXIT_SUCCESS;
}

void printCode(deque<bool> ptr) {

        // deque<bool>
        for (int i = 0; i < ptr.size(); i++) {
                if (ptr[i])
                        cout << "1";
                else
                        cout << "0";
        }
}
