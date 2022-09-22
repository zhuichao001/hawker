#pragma once

#include <assert.h>

const double LOAD_RATIO = 0.7;
const int SLOT_COUNT = 32;

template<typename K, typename T>
struct hash_node{
    K key;
    T val;
    hash_node *prev;
    hash_node *next;
    hash_node(const K &k="", const T &v=""):
        key(k),
        val(v),
        prev(this),
        next(this){
    }
};

template<typename K, typename T>
int del_node(struct hash_node<K,T> *node){
    assert(node!=node->next);

    node->next->prev = node->prev;
    node->prev->next = node->next;
    delete node;
    return 0;
}

template<typename K, typename T>
void add_node(struct hash_node<K,T> *head, struct hash_node<K,T> *node){
    assert(head!=nullptr);

    node->prev = head;
    node->next = head->next;
    head->next->prev = node;
    head->next = node;
}

template<typename K, typename T>
class hash_map {
public:
    hash_map(int n=SLOT_COUNT){
        init(0, n);
        idx_ = 0;
        table_[1] = nullptr;
        size_ = 0;
        rehash_pos_ = -1;
    }

    void init(int index, int count){
        num_[index] = count;
        table_[index] = new hash_node<K,T>[count];
        for(int i=0; i<count; ++i){
            table_[index][i].next = &table_[index][i];
            table_[index][i].prev = &table_[index][i];
        }
    }

    void try_rehash(){
        if(rehash_pos_==-1 && float(size_)/num_[idx_] > LOAD_RATIO){
            init(1-idx_, num_[idx_]<<1);
            rehash_pos_ = 0;
        }

        if(is_rehashing()){
            rehash_slot(rehash_pos_++); 

            //if rehash done, switch to new table
            if(rehash_pos_ >= num_[idx_]){
                printf("rehash done\n");
                rehash_pos_ = -1;
                delete []table_[idx_];
                table_[idx_] = nullptr;
                num_[idx_] = 0;
                idx_ = 1-idx_;
            }
        }

    }

    int insert(const K &key, const T &val){
        try_rehash();

        struct hash_node<K,T> *dst;
        if(find_node(key, dst)==0){ //update
            dst->val = val; 
            return 1;
        }else{
            const int dst_idx = is_rehashing() ? 1-idx_ : idx_;
            const unsigned int pos = (unsigned int)key_hash(key) % num_[dst_idx];
            struct hash_node<K,T> *head = &table_[dst_idx][pos];
            struct hash_node<K,T> *neo = new struct hash_node<K,T>(key, val);
            add_node(head, neo);
            ++size_;
            return 0;
        }
    }

    int find(const K &key, T &val){
        try_rehash();

        struct hash_node<K,T>* node;
        int err = find_node(key, node);
        if(err<0){
            return -1;
        }
        val = node->val;
        return 0;
    }

    int remove(const K &key){
        try_rehash();

        struct hash_node<K,T>* node;
        int err = find_node(key, node);
        if(err==0){
            del_node(node);
            --size_;
        }
        return err;
    }

    int size() const {
        return size_;
    }

    void print(){
        for(int i=0; i<num_[idx_]; ++i){
            const struct hash_node<K,T> *head = &table_[idx_][i];
            struct hash_node<K,T> *from = head->next;
            printf("slot:%d\n  ", i);
            while(from!=head){
                struct hash_node<K,T> *forward = from->next;
                printf("<%s:%s> ", from->key.c_str(), from->val.c_str());
                from = forward;
            }
            printf("\n");
        }
    }

private:
    bool is_rehashing(){
        return rehash_pos_>=0;
    }

    void rehash_slot(const int pos){
        struct hash_node<K,T> *head = &table_[idx_][pos];
        struct hash_node<K,T> *from = head->next;
        while(from!=head){
            struct hash_node<K,T> *forward = from->next;

            const unsigned int to_pos = (unsigned int)key_hash(from->key) % num_[1-idx_];
            struct hash_node<K,T>* to_head = &table_[1-idx_][to_pos];
            add_node(to_head, from);

            from = forward;
        }
        head->next = head;
        head->prev = head;
    }

    int find_node(const K &key, struct hash_node<K,T>* &dst){
        const unsigned int hash_val = (unsigned int)key_hash(key);
        if(is_rehashing()){
            int pos =  hash_val % num_[1-idx_];
            struct hash_node<K,T>* head = &table_[1-idx_][pos];
            if(find_list(head, key, dst)==0){
                return 0;
            }
        }
        int pos = hash_val % num_[idx_]; //TODO: DEBUG
        struct hash_node<K,T>* head = &table_[idx_][pos];
        return find_list(head, key, dst);
    }

    int find_list(const struct hash_node<K,T> *head, const K &key, struct hash_node<K,T>* &dst){
        struct hash_node<K,T> *cur = head->next;
        while(cur!=head){
            if(cur->key == key){
                dst = cur;
                return 0;
            }
            cur = cur->next;
        }
        return -1;
    }

    int num_[2];
    hash_node<K,T> *table_[2];
    int idx_ = 0;

    int size_;
    int rehash_pos_;

    std::hash<K> key_hash;
};
