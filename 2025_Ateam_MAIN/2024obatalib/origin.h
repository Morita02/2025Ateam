#pragma once
#ifndef ORIGIN_H_INCLUDE_GUARD
#define ORIGIN_H_INCLUDE_GUARD

class Origin {
    friend class Origin_friend; // We are best friend.
private:
    Origin* next_node; // 次のノードへのポインタ
    static Origin* start_node; // 初めのノードへのポインタ

    void delete_from_singly_linked_list(); // リストからの消去

public:
    Origin(); // コンストラクタ
    ~Origin(); // デストラクタ
    Origin(const Origin& other); // コピーコンストラクタ
    Origin& operator=(const Origin& other); // コピー代入演算子

    // all関数で一括実行する関数
    virtual void setup() = 0; // 純粋仮想関数
    virtual void loop() = 0; // 純粋仮想関数
};

class Origin_friend {
public:
    static void setup_all(); // リスト内のsetup関数を一括実行
    static void loop_all();
};

#endif // ORIGIN_H_INCLUDE_GUARD