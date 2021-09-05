#include "bptree.h"
#include <assert.h>


bpnode * bpindex::descend(const string &key){
    if(_size==0){
        return nullptr;
    }

    for(int i=0; i<_size; ++i){
        if(key<_index[i]){
            return _childs[i];
        }
    }
    return _childs[_size];
}

int bpindex::insert(bpnode * after_son, bpnode * new_son){
    assert(!full());

    //printf("after son:%p, size=%d\n", after_son, _size);
    int pos = -1;
    for(int i=0; i<=_size; ++i){
        if(after_son==_childs[i]){
            pos = i;
            break;
        }
        //printf("child:%p ", _childs[i]);
    }
    //printf("\n");

    assert(pos!=-1);

    for(int i=_size; i>pos; --i){
        _index[i] = _index[i-1];
        _childs[i+1] = _childs[i];
    }

    _index[pos] = new_son->minkey();
    _childs[pos+1] = new_son;
    _size += 1;

    return 0;
}

int bpindex::erase(bpnode * son){
    int pos = -1;
    for(int i=0; i<_size; ++i){
        if(son==_childs[i]){
            pos = i;
            break;
        }
    }
    
    if(pos==-1){
        return -1;
    }

    for(int i=pos; i<_size-1; ++i){
        _index[i] = _index[i+1];
        _childs[i] = _childs[i+1];
    }

    _childs[_size-1] = nullptr;
    _size -= 1;

    return 0;
}

bpnode * bpindex::divide(){
    bpindex * neo = new bpindex;
    neo->_parent = _parent; 
    int j =0;
    for(int i=_size/2; i<_size-1; ++i, ++j){
        neo->_index[j] = _index[i+1];
        neo->_childs[j] = _childs[i+1];
        neo->_childs[j]->_parent = neo;
    }
    neo->_childs[j] = _childs[_size];
    neo->_childs[j]->_parent = neo;
    neo->_size = _size/2;
    _size = _size/2;
    return neo;
}

//--------------------------------------------

bpnode * bpleaf::divide(){
    bpleaf *neo = new bpleaf;
    neo->_parent = _parent; 
    for(int i=_size/2; i<_size; ++i){
        neo->_keys[i-_size/2] = _keys[i];
        neo->_dats[i-_size/2] = _dats[i];
    }
    neo->_size = _size - _size/2;
    _size -= neo->_size;

    neo->_next = this->_next;
    this->_next = neo;
    return neo;
}

int bpleaf::get(const string &key, string &val){
    for(int i=0; i<ROADS; ++i){
        if(key==_keys[i]){
            val = _dats[i];
            return 0;
        }
    }
    return -1;
}

int bpleaf::put(const string &key, const string &val){
    if(full()){
        return -1;
    }

    int pos = 0;
    for(int i=0; i<_size; ++i){
        if(key>_keys[i]){
            pos = i+1;
        }else{
            break;
        }
    }

    for(int i=_size; i>pos; --i){
        _keys[i] = _keys[i-1];
        _dats[i] = _dats[i-1];
    }
    _keys[pos] = key;
    _dats[pos] = val;
    _size += 1;

    return 0;
}

int bpleaf::del(const string &key){
    int pos = -1;
    for(int i=0; i<_size; ++i){
        if(key==_keys[i]){
            pos = i;
            break;
        }
    }
    if(pos==-1){
        return -1;
    }

    for(int i=pos; i<_size-1; ++i){
        _keys[i] = _keys[i+1];
        _dats[i] = _dats[i+1];
    }
    _size -= 1;

    return 0;
}

//--------------------------------------------

bpnode * bptree::findbottom(const string &key){
    bpnode *cur = _root;
    bpnode *son = nullptr;
    while(true){
        son = dynamic_cast<bpindex*>(cur)->descend(key);
        if(son==nullptr || son->isleaf()){
            break;
        }
        cur = son;
    }
    return cur;
}

int bptree::get(const string &key, string &val){
    if(_root->isleaf()){
        return dynamic_cast<bpleaf*>(_root)->get(key, val);
    }

    bpnode *node = findbottom(key);
    bpnode *dst = dynamic_cast<bpindex*>(node)->descend(key);
    if(dst==nullptr){
        return -1;
    }
    return dynamic_cast<bpleaf*>(dst)->get(key, val);
}

int bptree::put(const string &key, const string &val){
    if(_root->isleaf()){
        dynamic_cast<bpleaf*>(_root)->put(key, val);
        if(_root->full()){
            split(_root);
        }
        return 0;
    }

    bpindex *node = dynamic_cast<bpindex*>(findbottom(key));
    bpleaf *leaf = dynamic_cast<bpleaf*>(node->descend(key));

    leaf->put(key, val);

    if(leaf->full()){
        split(leaf);
    }
    return 0;
}

//TODO debug
int bptree::del(const string &key){
    if(_root->isleaf()){
        dynamic_cast<bpleaf*>(_root)->del(key);
        return 0;
    }

    bpnode *node = findbottom(key);
    bpnode *dst = dynamic_cast<bpindex*>(node)->descend(key);
    
    assert(dst!=nullptr);

    dynamic_cast<bpleaf*>(dst)->del(key);

    while(dst->empty() && !dst->isroot()){
        dynamic_cast<bpindex*>(dst->parent())->erase(dst);
        bpnode * rabish = dst;
        dst = dst->parent();
        delete rabish;
    }

    if(dst->isroot() && dst->_size==1){
         bpnode * rabish = _root;
        _root = dynamic_cast<bpindex*>(_root)->_childs[0];
        delete rabish;
    }
    return 0;
}

int bptree::scan(const string &start, const string &end){
    //TODO next version
    return 0;
}

int bptree::split(bpnode *orig){
    assert(orig->full());

    bpnode *neo = orig->divide();

    if(orig->isroot()){
        _root = new bpindex(orig, neo);
        orig->set_parent(dynamic_cast<bpindex*>(_root));
        neo->set_parent(dynamic_cast<bpindex*>(_root));
        return 0;
    }

    dynamic_cast<bpindex*>(orig->parent())->insert(orig, neo);

    if(orig->parent()->full()){
        split(orig->parent());
    }
    return 0;
}

int bptree::print(){
    list<std::pair<bpnode *, int>> nodes;
    nodes.push_back(std::pair<bpnode *, int>(_root, 1));
    int round = 0;
    while(!nodes.empty()){
        std::pair<bpnode *, int> item = nodes.front();
        nodes.pop_front();

        bpnode *tmp = item.first;
        int level = item.second;
        if(level > round){
            ++round;
            printf("level:%d\n", level);
        }

        tmp->print();

        if(!tmp->isleaf()){
            bpindex *node = dynamic_cast<bpindex*>(tmp);
            for(int i=0; i<=node->_size; ++i){
                nodes.push_back(std::pair<bpnode *, int>(node->_childs[i], level+1));
            }
        }
    }
    printf("end print tree===========================\n");
    return 0;
}
