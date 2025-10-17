#include "origin.h"
#include <iostream>

using namespace std;

Origin* Origin::start_node = (NULL); // nullptrだった

// コンストラクタ
Origin::Origin() : next_node(NULL) {
    if (start_node == NULL) {
        start_node = this;
        cout << "最初のノード追加: " << this << endl;
    }
    else {
        Origin* last = start_node;
        while (last->next_node != NULL) {
            last = last->next_node;
        }
        last->next_node = this;
        cout << "新しいノード追加: " << this << " (最後尾)" << endl;
    }
}

// コピーコンストラクタ
Origin::Origin(const Origin& other) : next_node(NULL) {
    if (start_node == NULL) {
        start_node = this;
    }
    else {
        Origin* last = start_node;
        while (last->next_node != NULL) {
            last = last->next_node;
        }
        last->next_node = this;
    }
}

// コピー代入演算子
Origin& Origin::operator=(const Origin& other) {
    if (this != &other) {
        delete_from_singly_linked_list();
        if (start_node == NULL) {
            start_node = this;
        }
        else {
            Origin* last = start_node;
            while (last->next_node != NULL) {
                last = last->next_node;
            }
            last->next_node = this;
            next_node = NULL;
        }
    }
    return *this;
}

// デストラクタ
Origin::~Origin() {
    cout << "デストラクタ呼び出し: " << this << endl;
    delete_from_singly_linked_list();
}

// リストからの消去
void Origin::delete_from_singly_linked_list() {
    cout << "削除開始: " << this << endl;
    if (start_node == this) {
        start_node = next_node;
        cout << "先頭ノード削除: 新しい先頭 = " << start_node << endl;
        return;
    }

    Origin* current = start_node;
    Origin* prev = NULL;
    while (current != NULL && current != this) {
        prev = current;
        current = current->next_node;
    }

    if (current == this && prev != NULL) {
        prev->next_node = next_node;
        cout << "ノード削除: prev = " << prev << ", next = " << next_node << endl;
    }
}

// リスト内のsetup関数を一括実行
void Origin_friend::setup_all() {
    cout << "setup_all 開始" << endl;
    Origin* current = Origin::start_node;
    int count = 0;
    while (current != NULL) {
        cout << "setup対象: " << current << " (count: " << count << ")" << endl;
        current->setup();
        current = current->next_node;
        count++;
    }
    cout << "setup_all 終了" << endl;
}

// リスト内のloop関数を一括実行
void Origin_friend::loop_all() {
    cout << "loop_all 開始" << endl;
    Origin* current = Origin::start_node;
    int count = 0;
    while (current != NULL) {
        cout << "loop対象: " << current << " (count: " << count << ")" << endl;
        current->loop();
        current = current->next_node;
        count++;
    }
    cout << "loop_all 終了" << endl;
}
