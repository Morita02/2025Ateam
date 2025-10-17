#include "origin.h"
#include <iostream>

using namespace std;

Origin* Origin::start_node = (NULL); // nullptr������

// �R���X�g���N�^
Origin::Origin() : next_node(NULL) {
    if (start_node == NULL) {
        start_node = this;
        cout << "�ŏ��̃m�[�h�ǉ�: " << this << endl;
    }
    else {
        Origin* last = start_node;
        while (last->next_node != NULL) {
            last = last->next_node;
        }
        last->next_node = this;
        cout << "�V�����m�[�h�ǉ�: " << this << " (�Ō��)" << endl;
    }
}

// �R�s�[�R���X�g���N�^
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

// �R�s�[������Z�q
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

// �f�X�g���N�^
Origin::~Origin() {
    cout << "�f�X�g���N�^�Ăяo��: " << this << endl;
    delete_from_singly_linked_list();
}

// ���X�g����̏���
void Origin::delete_from_singly_linked_list() {
    cout << "�폜�J�n: " << this << endl;
    if (start_node == this) {
        start_node = next_node;
        cout << "�擪�m�[�h�폜: �V�����擪 = " << start_node << endl;
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
        cout << "�m�[�h�폜: prev = " << prev << ", next = " << next_node << endl;
    }
}

// ���X�g����setup�֐����ꊇ���s
void Origin_friend::setup_all() {
    cout << "setup_all �J�n" << endl;
    Origin* current = Origin::start_node;
    int count = 0;
    while (current != NULL) {
        cout << "setup�Ώ�: " << current << " (count: " << count << ")" << endl;
        current->setup();
        current = current->next_node;
        count++;
    }
    cout << "setup_all �I��" << endl;
}

// ���X�g����loop�֐����ꊇ���s
void Origin_friend::loop_all() {
    cout << "loop_all �J�n" << endl;
    Origin* current = Origin::start_node;
    int count = 0;
    while (current != NULL) {
        cout << "loop�Ώ�: " << current << " (count: " << count << ")" << endl;
        current->loop();
        current = current->next_node;
        count++;
    }
    cout << "loop_all �I��" << endl;
}
