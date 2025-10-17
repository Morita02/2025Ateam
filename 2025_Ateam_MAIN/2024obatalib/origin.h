#pragma once
#ifndef ORIGIN_H_INCLUDE_GUARD
#define ORIGIN_H_INCLUDE_GUARD

class Origin {
    friend class Origin_friend; // We are best friend.
private:
    Origin* next_node; // ���̃m�[�h�ւ̃|�C���^
    static Origin* start_node; // ���߂̃m�[�h�ւ̃|�C���^

    void delete_from_singly_linked_list(); // ���X�g����̏���

public:
    Origin(); // �R���X�g���N�^
    ~Origin(); // �f�X�g���N�^
    Origin(const Origin& other); // �R�s�[�R���X�g���N�^
    Origin& operator=(const Origin& other); // �R�s�[������Z�q

    // all�֐��ňꊇ���s����֐�
    virtual void setup() = 0; // �������z�֐�
    virtual void loop() = 0; // �������z�֐�
};

class Origin_friend {
public:
    static void setup_all(); // ���X�g����setup�֐����ꊇ���s
    static void loop_all();
};

#endif // ORIGIN_H_INCLUDE_GUARD