#include "bptree.h"
#include <list>


bpleaf * bptree::find(const std::string &key){
    if(_root->isleaf()){
        return dynamic_cast<bpleaf*>(_root);
    }

    bpindex *cur = dynamic_cast<bpindex*>(_root);
    while(true){
        bpnode *son = dynamic_cast<bpindex*>(cur)->descend(key);
        if(son==nullptr || son->isleaf()){
            break;
        }
        cur = dynamic_cast<bpindex*>(son);
    }
    return dynamic_cast<bpleaf*>(cur->descend(key));
}

int bptree::get(const std::string &key, std::string &val){
    bpleaf *dst = find(key);
    if(dst==nullptr){
        return -1;
    }
    return dst->get(key, val);
}

int bptree::put(const std::string &key, const std::string &val){
    bpleaf *dst = find(key);
    if(dst==nullptr){
        return -1;
    }

    dst->put(key, val);
    if(dst->full()){
        split(dst);
    }
    return 0;
}

int bptree::del(const std::string &key){
    bpnode *dst = find(key);
    if(dst==nullptr){
        return -1;
    }

    int err = dynamic_cast<bpleaf*>(dst)->del(key);
    if(dst->isroot() || err<0){
        return err;
    }

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

        dst = rebalance(dst);
    }

    return 0;
}

int bptree::scan(const std::string &start, const std::string &end, std::vector<kvpair> &res){
    bpleaf *dst = find(start);
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

    Reaction action = NONE;
    if(ln!=nullptr && rn!=nullptr){
        if(ln->fecund()){
            action = BRING_FROM_LEFT;
        }else if(rn->fecund()){
            action = BRING_FROM_RIGHT;
        }else{
            action = MERGE_TO_LEFT;
        }
    }else if(ln==nullptr && rn!=nullptr){
        if(rn->fecund()){
            action = BRING_FROM_RIGHT;
        }else{
            action = MERGE_TO_RIGHT;
        }
    } else if(ln!=nullptr && rn==nullptr){
        if(ln->fecund()){
            action = BRING_FROM_LEFT;
        }else{
            action = MERGE_TO_LEFT;
        }
    } else { //ln==nullptr && rn==nullptr
        _root = node;
        _root->_parent = nullptr;
        return node;
    }

    if(action==BRING_FROM_LEFT){
        node->bringtail(ln);
        upindex(node);
        upindex(ln);
        return node->parent();
    }else if(action==BRING_FROM_RIGHT){
        node->bringhead(rn);
        upindex(node);
        upindex(rn);
        return node->parent();
    }else if(action==MERGE_TO_LEFT){
        ln->extend(node);
        bpindex * parent = dynamic_cast<bpindex*>(node->_parent);
        parent->erase(node);
        upindex(node->_parent);
        delete node;
        return parent;
    }else if(action==MERGE_TO_RIGHT){
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

//update node's index in parent
void bptree::upindex(bpnode *node){
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
    if(!orig->full()){
        return -1;
    }

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

void bptree::print(){
    std::list<std::pair<bpnode *, int>> nodes; //<node, level>
    nodes.push_back(std::pair<bpnode *, int>(_root, 1));
    while(!nodes.empty()){
        std::pair<bpnode *, int> item = nodes.front();
        nodes.pop_front();
        bpnode *tmp = item.first;
        if(tmp->isleaf()){ //print leaf node
            bpleaf *cur = dynamic_cast<bpleaf*>(tmp);
            printf("    leaf: %p size:%d next:%p parent:%p \n", this, cur->_size, cur->_next, cur->_parent);
            for(int i=0; i<cur->_size; ++i){
                printf("        %s->%s  ", cur->_keys[i].c_str(), cur->_dats[i].c_str());
            }
            printf(cur->_size==0?"        [EMPTY]\n":"\n");
        }else{ //print index node
            bpindex *cur = dynamic_cast<bpindex*>(tmp);
            printf("[index node]: %p parent: %p\n", cur, cur->_parent);
            for(int i=0; i<cur->_size; ++i){
                printf("  index:%s  ", cur->_index[i].c_str());
            }
            printf("\n");
            for(int i=0; i<=cur->_size; ++i){
                printf("  child:%p  ", cur->_childs[i]);
            }
            printf("\n");

            for(int i=0; i<=cur->_size; ++i){
                nodes.push_back(std::pair<bpnode *, int>(cur->_childs[i], item.second+1));
            }
        }
    }
    printf("END PRINT TREE......\n\n");
}
