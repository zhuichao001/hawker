#include <map>
#include <string>
#include <iostream>

template<typename Vtype>
class FreqNode;

template<typename Vtype>
class Node{
public:
    std::string key;
    Vtype val;   
    Node<Vtype> *up;
    Node<Vtype> *down;
    FreqNode<Vtype> *slot;

    Node(const std::string &k, const Vtype &v):
        key(k),
        val(v){
        slot = nullptr;
        up = nullptr; 
        down = nullptr;
    }
};

template<typename Vtype>
class FreqNode{
public:
    int freq;
    FreqNode<Vtype> *prev;
    FreqNode<Vtype> *post;
    Node<Vtype> *first;
    Node<Vtype> *last;

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

    void remove(Node<Vtype> *node){
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

    Node<Vtype> *pop(){
        if(first==nullptr){
            return NULL; 
        }

        Node<Vtype> *res = first;;
        first = first->down;
        if(first==nullptr){
            last = nullptr;
        }
        return res;
    }

    void append(Node<Vtype> *node){
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

template<typename Vtype>
class LFUCache{
    std::map<std::string, Node<Vtype>*> cache;
    int size;
    const int capacity;
    FreqNode<Vtype> freq_list;

public:
    LFUCache(int c):
        size(0),
        capacity(c),
        freq_list(0){
    }

    int get(const std::string &key, Vtype &val){
        auto it = cache.find(key);
        if(it != cache.end()){
            Node<Vtype> *node = it->second;
            val = node->val;
            inc_freq(node);
            return 0;
        } else {
            return -1;
        }
    }

    void put(const std::string &key, Vtype &val){
        auto it = cache.find(key);
        if(it != cache.end()){ //update
            Node<Vtype> *node = it->second;
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

            Node<Vtype> *node = new Node<Vtype>(key, val);
            freq_list.post->append(node);
            cache[key] = node;
            ++size;
        }
    }

    void display(){
        FreqNode<Vtype> *cur = freq_list.post;
        while(cur!=nullptr){
            std::cout<<"freq "<<cur->freq<<":";
            Node<Vtype> *node = cur->first;
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
    void add_slot(FreqNode<Vtype> *br, int freq){
        FreqNode<Vtype> *tmp = new FreqNode<Vtype>(freq);
        if(br->post != nullptr){
            tmp->post = br->post;
            br->post->prev = tmp;
        }
        tmp->prev = br;
        br->post = tmp;
    }

    void del_slot(FreqNode<Vtype> *br){
        if(br->post!=nullptr){
            br->post->prev = br->prev;      
        }
        if(br->prev!=nullptr){
            br->prev->post = br->post;
        }
        delete br;
    }

    void inc_freq(Node<Vtype> *node){
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
