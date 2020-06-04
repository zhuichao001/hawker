package main


import(
    "hash/crc32"
    "sort"
    "errors"
    "fmt"
)

const(
    SCALE_N = 110137 //generate N virtual nodes per real node, the bigger Num get better banlance
)

func HashInt(str string) uint32 {
	return crc32.ChecksumIEEE([]byte(str))
}

type Item struct {
    id uint32
    key string
}

type Node struct {
    name string
    id uint32
    vnodes []*VirtualNode
}

func (node *Node) KeyNums() (n int) {
    for _, vnode := range(node.vnodes) {
        n += len(vnode.items)
    }
    return
}

type VirtualNode struct {
    vname string
    vid uint32
    belong *Node
    items []*Item
}

func NewNode(nodename string) (node *Node) {
    nodeid := HashInt(nodename) 
    node = &Node{name:nodename, id:nodeid, vnodes:make([]*VirtualNode, SCALE_N)} 
    for i := 0; i<SCALE_N; i++ {
        vname := fmt.Sprintf("nodeid:%d#idx:%d", nodeid, i)
        vid := HashInt(vname)
        node.vnodes[i] = &VirtualNode{vname, vid, node, make([]*Item, 0)} 
    }
    return
}

type ConsistHash struct {
    nodes map[string]*Node
    vnodes []*VirtualNode
}

func NewConsistHash(nodenames []string) (ch *ConsistHash) {
    ch = &ConsistHash{
        nodes: make(map[string]*Node, len(nodenames)),
        vnodes: make([]*VirtualNode, 0),
    }

    for _, name := range(nodenames) {
        ch.AddNode(name)
    }
    return 
}

func (ch *ConsistHash) AddNode(nodename string) error {
    if _, ok := ch.nodes[nodename]; ok {
        return errors.New(fmt.Sprintf("[node=%s] has exist", nodename))
    }

    node := NewNode(nodename)
    ch.nodes[nodename] = node
    ch.vnodes = append(ch.vnodes, node.vnodes...)

    sort.Slice(ch.vnodes, func(i,j int) bool {
        return ch.vnodes[i].vid < ch.vnodes[j].vid
    })
    return nil
}

func (ch *ConsistHash) getVirtualNode(id uint32) *VirtualNode {
    i, j := 0, len(ch.vnodes)-1
    mid, found := 0, false
    for i<=j {
        mid = (i+j)/2
        if ch.vnodes[mid].vid >= id {
            if mid == 0 || ch.vnodes[mid-1].vid < id {
                found = true
                break
            }
            j = mid - 1
        } else {
            i = mid + 1
        }
    }
    if !found {
        mid = 0
    }

    return ch.vnodes[mid]
}

func (ch *ConsistHash) AddKey(keyname string) (node *Node) {
    keyid := HashInt(keyname)
    vnode := ch.getVirtualNode(keyid) 
    vnode.items = append(vnode.items, &Item{keyid, keyname})
    return vnode.belong
}

func main() {
    nodenames := []string{"102.68.1.101:7366", "102.68.1.101:7367", "102.68.1.101:7368", "102.68.1.101:7369", "102.68.1.101:7370", "102.68.1.101:7371"}
    ch := NewConsistHash(nodenames)

    for i:=0; i<1000000; i++ {
        key := fmt.Sprintf("%d", i*i)
        ch.AddKey(key)
    }

    for nodename, node := range(ch.nodes) {
        fmt.Printf("node:%s, item nums:%d\n", nodename, node.KeyNums())
    }
}
