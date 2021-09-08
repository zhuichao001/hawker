#include "bptree.h"
#include <list>


bpnode * bpnode::leftside(){
    if(_parent==nullptr){
        return nullptr;
    }

    int pos = dynamic_cast<bpindex*>(_parent)->offset(this);
    if(pos==0){
        bpindex * uncle = dynamic_cast<bpindex*>(_parent->leftside());
        if(uncle==nullptr){
            return nullptr;
        }
        return uncle->_childs[uncle->_size];
    }

    return dynamic_cast<bpindex*>(_parent)->_childs[pos-1];
}

bpnode * bpnode::rightside(){
    if(_parent==nullptr){
        return nullptr;
    }

    int pos = dynamic_cast<bpindex*>(_parent)->offset(this);
    if(pos==_parent->_size){
        bpindex * uncle = dynamic_cast<bpindex*>(_parent->rightside());
        if(uncle==nullptr){
            return nullptr;
        }
        return uncle->_childs[0];
    }

    return dynamic_cast<bpindex*>(_parent)->_childs[pos+1];
}

//----------------------------------

bpnode * bpindex::descend(const std::string &key){
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
    int pos = offset(after_son);
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

int bpindex::replace(bpnode * old, bpnode *neo){
    int pos = offset(old);
    assert(pos!=-1);
    _childs[pos] = neo;
    neo->_parent = this;
    return 0;
}

int bpindex::erase(bpnode * son){
    assert(!empty());
    int pos = offset(son);
    assert(pos!=-1);

    for(int i=(pos==0?1:pos); i<_size; ++i){
        _index[i-1] = _index[i];
    }

    for(int i=pos; i<_size; ++i){
        _childs[i] = _childs[i+1];
    }

    _childs[_size] = nullptr;
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
    neo->_size = (_size-1)/2;
    _size = _size/2;
    return neo;
}

void bpindex::extend(bpnode *rsib){
    //printf("%p _size:%d, rsib %p size:%d\n", this, _size, rsib, rsib->_size);
    assert(_size+rsib->_size<=ROADS);
    if(rsib->_size==0){
        _index[_size] = dynamic_cast<bpindex*>(rsib)->_childs[0]->minkey();
        _childs[_size+1] = dynamic_cast<bpindex*>(rsib)->_childs[0];
        _childs[_size+1]->_parent = this;
        _size += 1;
        return;
    }

    bpindex *from = dynamic_cast<bpindex*>(rsib);
    _index[_size] = from->_childs[0]->minkey();

    for(int i=0; i<from->_size; ++i){
        _index[_size+1+i] = from->_index[i];
        _childs[_size+1+i] = from->_childs[i];
        from->_childs[i]->_parent = this;
    }
    _childs[_size+1+from->_size] = from->_childs[from->_size];
    from->_childs[from->_size]->_parent = this;

    _size += 1+from->_size;
}

void bpindex::bringhead(bpnode *from){
    bpindex *rb = dynamic_cast<bpindex*>(from);
    bpnode *child = rb->_childs[0];
    child->_parent = this;
    _index[_size] = child->minkey();
    _childs[_size+1] = child;
    _size += 1;

    rb->_size -=1;
    for(int i=0; i<rb->_size; ++i){
        rb->_index[i] = rb->_index[i+1];
        rb->_childs[i] = rb->_childs[i+1];
    }
    rb->_childs[rb->_size] = rb->_childs[rb->_size+1];
}

void bpindex::bringtail(bpnode *from){
    bpindex *lb = dynamic_cast<bpindex*>(from);
    bpnode *child = lb->_childs[lb->_size];
    child->_parent = this;
    lb->_size -= 1;

    _childs[_size+1] = _childs[_size];
    for(int i=_size; i>0; --i){
        _index[i] = _index[i-1];
        _childs[i] = _childs[i-1];
    }
    _index[0] = _childs[1]->minkey();
    _childs[0] = child;
    _size += 1;
}

int bpindex::offset(bpnode *son){
    bpnode **dst = std::find(_childs, _childs+_size, son);
    assert(dst!=nullptr);
    return dst-_childs;
}

void bpindex::print(){
    printf("[index node]: %p parent: %p\n", this, _parent);
    for(int i=0; i<_size; ++i){
        printf("  index:%s  ", _index[i].c_str());
    }
    printf("\n");
    for(int i=0; i<=_size; ++i){
        printf("  child:%p  ", _childs[i]);
    }
    printf("\n");
}

//----------------------------------

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

void bpleaf::extend(bpnode *rsib){
    assert(_size+rsib->_size<=ROADS);

    bpleaf *from = dynamic_cast<bpleaf *>(rsib);
    for(int i=0; i<from->_size; ++i){
        _keys[_size+i] = from->_keys[i];
        _dats[_size+i] = from->_dats[i];
    }
    _size += from->_size;
    from->_size = 0;
   _next = from->_next;
}

int bpleaf::get(const std::string &key, std::string &val){
    for(int i=0; i<ROADS; ++i){
        if(key==_keys[i]){
            val = _dats[i];
            return 0;
        }
    }
    return -1;
}

int bpleaf::put(const std::string &key, const std::string &val){
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

int bpleaf::del(const std::string &key){
    int pos = -1;
    for(int i=0; i<_size; ++i){
        if(key==_keys[i]){
            pos = i;
            break;
        }
    }
    //printf("leaf %p find %s, size:%d pos:%d\n", this, key.c_str(), _size, pos);
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

void bpleaf::bringhead(bpnode *from){
    bpleaf *rb = dynamic_cast<bpleaf*>(from);
    _keys[_size] = rb->_keys[0];
    _dats[_size] = rb->_keys[0];
    _size += 1;

    rb->_size -=1;
    for(int i=0; i<rb->_size; ++i){
        rb->_keys[i] = rb->_keys[i+1];
        rb->_dats[i] = rb->_dats[i+1];
    }
}

void bpleaf::bringtail(bpnode *from){
    bpleaf *lb = dynamic_cast<bpleaf*>(from);
    std::string k = lb->_keys[lb->_size-1];
    std::string v = lb->_dats[lb->_size-1];
    lb->_size -= 1;

    for(int i=_size; i>0; --i){
        _keys[i] = _keys[i-1];
        _dats[i] = _dats[i-1];
    }
    _keys[0] = k;
    _dats[0] = v;
    _size += 1;
}

void bpleaf::print(){
    printf("    leaf: %p size:%d next:%p parent:%p \n", this, _size, _next, _parent);
    for(int i=0; i<_size; ++i){
        printf("        %s->%s  ", _keys[i].c_str(), _dats[i].c_str());
    }
    printf(_size==0?"        [EMPTY]\n":"\n");
}

//----------------------------------

bpnode * bptree::findbottom(const std::string &key){
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

int bptree::get(const std::string &key, std::string &val){
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

int bptree::put(const std::string &key, const std::string &val){
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

int bptree::del(const std::string &key){
    if(_root->isleaf()){
        return dynamic_cast<bpleaf*>(_root)->del(key);
    }

    bpnode *node = findbottom(key);
    bpnode *dst = dynamic_cast<bpindex*>(node)->descend(key);

    //printf("node:%p, dst:%p, %s\n", node, dst, dst->isleaf()?"leaf":"index");

    int err = dynamic_cast<bpleaf*>(dst)->del(key);
    if(err<0){
        return err;
    }

    //int n=1;
    while(dst!=nullptr){
        if(dst->balanced()){
            break;
        }

        if(dst==_root){
            if(dst->_size==0){
                _root = dynamic_cast<bpindex*>(dst)->_childs[0];
                _root->_parent = nullptr;
                delete dst;
            }
            break;
        }
        //printf("rebalance time:%d, dst:%p, parent:%p\n", n++, dst, dst->parent());
        
        dst = rebalance(dst);
    }

    return 0;
}

int bptree::scan(const std::string &start, const std::string &end, std::vector<kvpair> &res){
    bpnode *node = findbottom(start);
    bpleaf *dst = dynamic_cast<bpleaf*>(dynamic_cast<bpindex*>(node)->descend(start));
    if(dst==nullptr){
        return -1;
    }

    while(dst!=nullptr){
        for(int i=0; i<dst->_size; ++i){
            if(dst->_keys[i] > end){
                return 0;
            }
            if(dst->_keys[i]>=start){
                res.push_back(std::make_pair(dst->_keys[i], dst->_dats[i]));
            }
        }
        dst = dst->_next;
    }
    return 0;
}

bpnode * bptree::rebalance(bpnode *node){
    bpnode *ln = node->leftside();
    bpnode *rn = node->rightside();
    //printf("node:%p, left:%p, right:%p\n", node, ln, rn);

    Reaction action = NOTHING;
    if(ln!=nullptr && rn!=nullptr){
        if(ln->redundant()){
            action = BORROW_LEFT;
        }else if(rn->redundant()){
            action = BORROW_RIGHT;
        }else{
            //printf("left:%p,right:%p is not redundant\n", ln, rn);
            action = MERGE_LEFT;
        }
    }else if(ln==nullptr && rn!=nullptr){
        if(rn->redundant()){
            action = BORROW_RIGHT;
        }else{
            action = MERGE_RIGHT;
        }
    } else if(ln!=nullptr && rn==nullptr){
        if(ln->redundant()){
            action = BORROW_LEFT;
        }else{
            //printf("...left:%p,is not redundant\n", ln);
            action = MERGE_LEFT;
        }
    } else { //ln==nullptr && rn==nullptr
        _root = node;
        _root->_parent = nullptr;
        return node;
    }
    //printf("action:%d\n", action);

    if(action==BORROW_LEFT){
        node->bringtail(ln);
        upindex(node);
        upindex(ln);
        return node->parent();
    }else if(action==BORROW_RIGHT){
        node->bringhead(rn);
        upindex(node);
        upindex(rn);
        return node->parent();
    }else if(action==MERGE_LEFT){
        ln->extend(node);
        bpindex * parent = dynamic_cast<bpindex*>(node->_parent);
        parent->erase(node);
        upindex(node->_parent);
        delete node;
        return parent;
    }else if(action==MERGE_RIGHT){
        node->extend(rn);
        bpindex * parent = dynamic_cast<bpindex*>(node->_parent);
        parent->erase(node);
        dynamic_cast<bpindex*>(rn->_parent)->replace(rn, node);
        upindex(node->_parent);
        delete rn;
        return parent;
    }
    return node;
}

void bptree::upindex(bpnode *node){
    //update parent index
    bpindex *parent = dynamic_cast<bpindex*>(node->parent());
    while(parent!=nullptr){
        int pos = parent->offset(node);
        if(pos>0){
            parent->_index[pos-1] = node->minkey();
            break;
        }
        node = parent;
        parent = parent->parent();
    }
}

int bptree::split(bpnode *orig){
    assert(orig->full());

    bpnode *neo = orig->divide();

    if(orig->isroot()){
        _root = new bpindex(orig, neo);
        orig->setparent(dynamic_cast<bpindex*>(_root));
        neo->setparent(dynamic_cast<bpindex*>(_root));
        return 0;
    }

    dynamic_cast<bpindex*>(orig->parent())->insert(orig, neo);

    if(orig->parent()->full()){
        split(orig->parent());
    }
    return 0;
}

int bptree::print(){
    std::list<std::pair<bpnode *, int>> nodes;
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
    printf("END PRINT TREE......\n\n");
    return 0;
}
