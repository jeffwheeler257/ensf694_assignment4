/*
 *  lookupTable.cpp
 *  ENSF 694 Lab 4 - Exercise A
 *  Created by Jeff Wheeler
 *  Submission date: July 26, 2024
 */

#include "lookupTable.h"

LT_Node::LT_Node(const Pair& pairA, LT_Node *nextA): pairM(pairA), nextM(nextA) {

}

LookupTable::LookupTable(): sizeM(0), headM(nullptr), cursorM(nullptr){

}

LookupTable::LookupTable(const LookupTable& source): sizeM(source.sizeM){
    if (source.sizeM == 0){
        headM = nullptr;
        cursorM = nullptr;
    }
    else if (source.sizeM == 1){
        headM = new LT_Node(source.headM->pairM, nullptr);
        if (headM == source.cursorM)
            cursorM = headM;
        else
            cursorM = nullptr;
    }
    else {
        headM = new LT_Node(source.headM->pairM, nullptr);
        cursorM = nullptr;
        LT_Node* next_node_ptr = source.headM->nextM;
        LT_Node* last_node_ptr = headM;
        for (int i = 1; i < source.sizeM; i ++){
            LT_Node* new_node = new LT_Node(next_node_ptr->pairM, nullptr);
            last_node_ptr->nextM = new_node;
            last_node_ptr = new_node;
            if (next_node_ptr == source.cursorM)
                cursorM = new_node;
            next_node_ptr = next_node_ptr->nextM;
        }
    }
}

LookupTable& LookupTable::operator=(const LookupTable& rhs){
    if(this != &rhs){
        this->sizeM = rhs.sizeM;
        this->destroy();
        if (rhs.sizeM == 0){
            headM = nullptr;
            cursorM = nullptr;
        }
        else if (rhs.sizeM == 1){
            headM = new LT_Node(rhs.headM->pairM, nullptr);
            if (headM == rhs.cursorM)
                cursorM = headM;
        }
        else {
            headM = new LT_Node(rhs.headM->pairM, nullptr);
            LT_Node* next_node_ptr = rhs.headM->nextM;
            LT_Node* last_node_ptr = headM;
            for (int i = 1; i < rhs.sizeM; i ++){
                LT_Node* new_node = new LT_Node(next_node_ptr->pairM, nullptr);
                last_node_ptr->nextM = new_node;
                last_node_ptr = new_node;
                if (next_node_ptr == rhs.cursorM)
                    cursorM = new_node;
                next_node_ptr = next_node_ptr->nextM;
            }
        }
    }
    return *this;
}

LookupTable::~LookupTable(){
    this->destroy();
}

void LookupTable::destroy(){
    LT_Node* this_node = headM;
    for (int i = 0; i < sizeM; i--){
        LT_Node* next_node = this_node->nextM;
        delete this_node;
        this_node = next_node;
    }
    headM = nullptr;
    cursorM = nullptr;
    sizeM = 0;
}

void LookupTable::copy(const LookupTable& source){
    LookupTable copy(source);
    *this = copy;
}

LookupTable& LookupTable::begin(){
    cursorM = headM;
    return *this;
}

int LookupTable::size() const {
    return sizeM;
}

int LookupTable::cursor_ok() const {
    if (cursorM == nullptr)
        return 0;
    return 1;
}

const int& LookupTable::cursor_key() const {
        return this->cursorM->pairM.key;
}

const Type& LookupTable::cursor_datum() const {
        return this->cursorM->pairM.datum;
}

void LookupTable::insert(const Pair& pairA) {
    if (headM == nullptr){
        LT_Node* new_node = new LT_Node(pairA, nullptr);
        headM = new_node;
        sizeM++;
        return;
    }
    cursorM = headM;
    LT_Node* last_node = nullptr;
    while(cursorM != nullptr){
        if (cursorM->pairM.key == pairA.key){
            cursorM->pairM.datum = pairA.datum;
            cursorM = nullptr;
            return;
        }
        else if (cursorM->pairM.key > pairA.key){ // check here
            if (cursorM == headM){
                LT_Node* new_node = new LT_Node(pairA, nullptr);
                headM = new_node;
                new_node->nextM = cursorM;
                cursorM = nullptr;
                sizeM++;
                return;
            }
            LT_Node* new_node = new LT_Node(pairA, nullptr);
            new_node->nextM = cursorM;
            last_node->nextM = new_node;
            cursorM = nullptr;
            sizeM++;
            return;
        }
        last_node = cursorM;
        cursorM = cursorM->nextM;
    }
    cursorM = headM;
    while(cursorM->nextM != nullptr){
        cursorM = cursorM->nextM;
    }
    LT_Node* new_node = new LT_Node(pairA, nullptr);
    cursorM->nextM = new_node;
    cursorM = nullptr;
    sizeM++;
}

int LookupTable::remove(const int& keyA) {
    cursorM = headM;
    if (cursorM->pairM.key == keyA){
        int removed_key = cursorM->pairM.key;
        headM = cursorM->nextM;
        delete cursorM;
        cursorM = nullptr;
        sizeM--;
        return removed_key;
    }
    cursorM = cursorM->nextM;
    LT_Node* last_node = headM;
    while(cursorM != nullptr){
        if(cursorM->pairM.key == keyA){
            int removed_key = cursorM->pairM.key;
            last_node->nextM = cursorM->nextM;
            delete cursorM;
            cursorM = nullptr;
            sizeM--;
            return removed_key;
        }
        last_node = cursorM;
        cursorM = cursorM->nextM;
    }
    cursorM = nullptr;
    return -1; // return -1 if table does not have keyA
}

void LookupTable::find(const int& keyA) {
    cursorM = headM;
    for (int i = 0; i < sizeM; i ++){
        if (cursorM->pairM.key == keyA){
            return;
        }
        cursorM = cursorM->nextM;
    }
    cursorM = nullptr;
}

void LookupTable::go_to_first() {
    if (sizeM > 0)
        cursorM = headM;
}

void LookupTable::step_fwd() {
    cursorM = cursorM->nextM;
}

void LookupTable::make_empty() {
    this->destroy();
}

void LookupTable::display() const {
        cout << "Key: " << cursorM->pairM.key << ", Data: " << cursorM->pairM.datum << endl;
}

bool LookupTable::isEmpty() const {
    if (sizeM == 0)
        return true;
    return false;
}

int* LookupTable::retrieve_at(int i) {
    if (i < 0 || i >= sizeM)
        return nullptr;
    
    LT_Node* node = headM;
    for (int j = 0; j < i; j++){
        node = node->nextM;
    }
    return &(node->pairM.key);
}

