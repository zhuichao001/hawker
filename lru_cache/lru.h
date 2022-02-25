#include <map>
#include <string>
#include <iostream>

template<typename KT, typename VT>
class NodeList;

template<typename KT, typename VT>
class LRUCache;

template<typename KT, typename VT>
class Node{
    KT key;
    VT val;   

    Node<KT, VT> *prev, *next;

    friend NodeList<KT, VT>;
    friend LRUCache<KT, VT>;
public:
    Node():
        prev(nullptr),
        next(nullptr){
    };

    Node(const KT &k, const VT &v):
        key(k),
        val(v){
        prev = nullptr; 
        next = nullptr;
    }
};

template<typename KT, typename VT>
class NodeList{
    Node<KT, VT> head;
public:
    NodeList():
        head(){
        head.next = &head;
        head.prev = &head;
    }

    bool empty(){
        return head.next == &head;
    }

    void remove(Node<KT,VT> *node){
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    Node<KT,VT> *pop(){
        if(empty()){
            return nullptr;
        }
        Node<KT,VT> *res = head.prev;;
        head.prev->next =  &head;
        head.prev = head.prev->prev;
        res->next = nullptr;
        res->prev = nullptr;
        return res;
    }

    void push(Node<KT,VT> *node){
        node->next = head.next;
        node->prev = &head;
        head.next->prev = node;
        head.next = node;
    }

    void update(Node<KT,VT> *node){
        node->next->prev = node->prev;
        node->prev->next = node->next;
        push(node);
    }

    void display(){
        Node<KT, VT> *node = head.next;
        while(node!=&head){
           std::cout<<"("<<node->key<<","<<node->val<<"), "; 
           node = node->next;
        }
        std::cout<<std::endl;
    }
};

template<typename KT, typename VT>
class LRUCache{
    std::map<KT, Node<KT,VT>*> cache;
    int size;
    const int capacity;
    NodeList<KT,VT> list;

public:
    LRUCache(int cap):
        size(0),
        capacity(cap),
        list(){
    }

    int get(const KT &key, VT &val){
        auto it = cache.find(key);
        if(it == cache.end()){
            return -1;
        }
        Node<KT,VT> *node = it->second;
        val = node->val;
        list.update(node);
        return 0;
    }

    void put(const KT &key, VT &val){
        auto it = cache.find(key);
        if(it != cache.end()){ //update
            Node<KT,VT> *node = it->second;
            node->val = val;
            list.update(node);
        } else { //add
            if(size==capacity){
                Node<KT,VT> *node = list.pop();
                cache.erase(node->key);
            }

            Node<KT,VT> *node = new Node<KT,VT>(key, val);
            list.push(node);
            cache[key] = node;
            ++size;
        }
    }

    void display(){
        list.display();
    }
};
