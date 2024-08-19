#include <map>
#include <assert.h>
#include <string>
#include <iostream>

template<typename VT>
class FreqNode;

template<typename VT>
class LFUCache;

template<typename VT>
struct Node{
    std::string key;
    VT val;   

    Node<VT> *prev, *next;
    FreqNode<VT> *slot;

    Node():{
        prev = this; 
        next = this;
        slot = nullptr;
    }

    Node(const std::string &k, const VT &v):
        key(k),
        val(v){
        Node();
    }
};

//FIFO
template<typename VT>
class FreqNode{
    int freq;
    Node<VT> dummy; 
    friend LFUCache<VT>;
public:
    FreqNode(int f): freq(f){
        assert(freq>0);
    }

    ~FreqNode(){
        while(!empty()){
            Node<VT> *node = pop();
            delete node;
        }
    }

    bool empty(){
        return dummy.next == &dummy;
    }

    void remove(Node<VT> *node){
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    Node<VT> *pop(){  //pop from head
        if(empty()){
            return nullptr; 
        }

        Node<VT> *res = dummy.next;
        remove(res);
        return res;
    }

    void push(Node<VT> *node){  //push to tail
        assert(node!=nullptr);
        node->prev = dummy.prev;
        node->next = &dummy;
        dummy.prev->next = node;
        dummy.prev = node;
    }

    void display(){
        Node<VT> *node = dummy.next;
        std::cout<<"    ";
        while(node!=&dummy){
           std::cout<<"("<<node->key<<","<<node->val<<"), "; 
           node = node->next;
        }
        std::cout<<std::endl;
    }
};

template<typename VT>
class LFUCache{
    int size;
    const int capacity;
    std::map<std::string, Node<VT>*> cache_map;
    std::map<int, FreqNode<VT> *> freq_map;

public:
    LFUCache(int cap):
        size(0),
        capacity(cap){
    }

    ~LFUCache(){
        for(const auto &pair : freq_map){
            delete pair.second;
        }
    }

    bool get(const std::string &key, VT &val){
        auto it = cache_map.find(key);
        if(it != cache_map.end()){
            Node<VT> *node = it->second;
            val = node->val;
            inc_freq(node);
            return true;
        } else {
            return false;
        }
    }

    void put(const std::string &key, VT &val){
        auto it = cache_map.find(key);
        if(it != cache_map.end()){ //prevdate
            Node<VT> *node = it->second;
            node->val = val;
            inc_freq(node);
        } else { //add
            if(size==capacity){
                eliminate(); //pepare quota
            }

            Node<VT> *node = new Node<VT>(key, val);
            inc_freq(node);

            cache_map[key] = node;
            ++size;
        }
    }

    void display(){
        for(const auto &pair : freq_map){
            if(pair.second->empty()){
                continue;
            }
            std::cout << "freq:" <<pair.second->freq << std::endl;
            pair.second->display();
        }
        std::cout << "-------------------" << std::endl;
    }

private:
    void eliminate(){
        for(auto it=freq_map.begin(); it!=freq_map.end(); ++it){
            if(!it->second->empty()){
                Node<VT> *node = it->second->pop();
                cache_map.erase(node->key);
                delete node;
                break;
            }
        }
    }

    void inc_freq(Node<VT> *node){
        int new_freq = 1;
        if(node->slot!=nullptr){
            node->slot->remove(node);
            new_freq = node->slot->freq + 1;
        }
        auto it = freq_map.find(new_freq);
        FreqNode<VT> *freq_node = nullptr;
        if(it==freq_map.end()){
            freq_node = new FreqNode<VT>(new_freq);
            freq_map[new_freq] = freq_node;
        }else{
            freq_node = it->second;
        }
        node->slot = freq_node;
        freq_node->push(node);
    }
};
