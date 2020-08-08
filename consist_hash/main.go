package main

import(
    "fmt"
)

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
