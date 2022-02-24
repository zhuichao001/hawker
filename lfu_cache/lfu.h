#include <map>
#include <string>
#include <iostream>

template<typename VT>
class FreqNode;

template<typename VT>
class LFUCache;

template<typename VT>
class Node{
    std::string key;
    VT val;   

    Node<VT> *up, *down;
    FreqNode<VT> *slot;

    friend FreqNode<VT>;
    friend LFUCache<VT>;
public:
    Node(const std::string &k, const VT &v):
        key(k),
        val(v){
        slot = nullptr;
        up = nullptr; 
        down = nullptr;
    }
};

template<typename VT>
class FreqNode{
    int freq;
    FreqNode<VT> *prev, *post;
    Node<VT> *first, *last;
    friend LFUCache<VT>;
public:

    FreqNode(int f):
        freq(f){
        prev = nullptr;
        post = nullptr;
        first = nullptr;
        last = nullptr;
    }

    bool empty(){
        return first == nullptr;
    }

    void remove(Node<VT> *node){
        if(node == first){
            first = first->down;
            if(first==nullptr){
                last = nullptr;
            }
            return;
        }

        if(node == last){
            last = last->up;
            if(last==nullptr){
                first = nullptr;
            }
            return;
        }

        node->up->down = node->down;
        node->down->up = node->up;
    }

    Node<VT> *pop(){
        if(first==nullptr){
            return NULL; 
        }

        Node<VT> *res = first;;
        first = first->down;
        if(first==nullptr){
            last = nullptr;
        }
        return res;
    }

    void append(Node<VT> *node){
        node->down = nullptr;
        node->slot = this;
        if(first == nullptr){
            first = last = node;
            return;
        }
        last->down = node;    
        node->up = last;
        last = node;
    }
};

template<typename VT>
class LFUCache{
    std::map<std::string, Node<VT>*> cache;
    int size;
    const int capacity;
    FreqNode<VT> freq_list;

public:
    LFUCache(int c):
        size(0),
        capacity(c),
        freq_list(0){
    }

    int get(const std::string &key, VT &val){
        auto it = cache.find(key);
        if(it != cache.end()){
            Node<VT> *node = it->second;
            val = node->val;
            inc_freq(node);
            return 0;
        } else {
            return -1;
        }
    }

    void put(const std::string &key, VT &val){
        auto it = cache.find(key);
        if(it != cache.end()){ //update
            Node<VT> *node = it->second;
            node->val = val;
            inc_freq(node);
            cache[key] = node;
        } else { //add
            if(size==capacity){
                if(freq_list.post!=nullptr){
                    freq_list.post->pop();
                }
            }

            if(freq_list.post==nullptr || freq_list.post->freq != 1){
                add_slot(&freq_list, 1);
            }

            Node<VT> *node = new Node<VT>(key, val);
            freq_list.post->append(node);
            cache[key] = node;
            ++size;
        }
    }

    void display(){
        FreqNode<VT> *cur = freq_list.post;
        while(cur!=nullptr){
            std::cout<<"freq "<<cur->freq<<":";
            Node<VT> *node = cur->first;
            while(node!=nullptr){
               std::cout<<"("<<node->key<<","<<node->val<<"),"; 
               node = node->down;
            }
            std::cout<<std::endl;
            cur = cur->post;
        }
        std::cout<<std::endl;
    }

private:
    void add_slot(FreqNode<VT> *br, int freq){
        FreqNode<VT> *tmp = new FreqNode<VT>(freq);
        if(br->post != nullptr){
            tmp->post = br->post;
            br->post->prev = tmp;
        }
        tmp->prev = br;
        br->post = tmp;
    }

    void del_slot(FreqNode<VT> *br){
        if(br->post!=nullptr){
            br->post->prev = br->prev;      
        }
        if(br->prev!=nullptr){
            br->prev->post = br->post;
        }
        delete br;
    }

    void inc_freq(Node<VT> *node){
        node->slot->remove(node);
        const int freq = node->slot->freq + 1;
        if(node->slot->post == nullptr || node->slot->post->freq != freq){
            add_slot(node->slot, freq);
        }

        if(node->slot->empty()){
            del_slot(node->slot);
        }

        node->slot->post->append(node);
    }
};
