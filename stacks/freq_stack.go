package main

import(
    "fmt"
    "errors"
)


type FreqStack struct {
    stacks map[int][]string
    freq map[string]int
    max_freq int
}

func NewFreqStack() (fs *FreqStack) {
    fs = &FreqStack{
        stacks: make(map[int][]string),
        freq: make(map[string]int),
        max_freq: 0,
    }
    return
}

func (fs *FreqStack) push (item string) {
    fs.freq[item] += 1
    if fs.freq[item] > fs.max_freq {
        fs.max_freq = fs.freq[item]
    }

    if _, ok := fs.stacks[fs.freq[item]]; !ok {
        fs.stacks[fs.freq[item]] = make([]string, 0)
    }
    fs.stacks[fs.freq[item]] = append(fs.stacks[fs.freq[item]], item)
}

func (fs *FreqStack) pop() (item string, err error) {
    if fs.max_freq ==0 {
        return "", errors.New("[error]FreqStack is empty")
    }
    stack,_ := fs.stacks[fs.max_freq] 
    item = stack[len(stack)-1]
    fs.freq[item] -= 1
    if len(stack) == 1 {
        delete(fs.stacks, fs.max_freq)
        dup := fs.max_freq-1
        for ; dup>0; dup-=1 {
            if _, ok:=fs.stacks[dup]; ok{
                break
            }
        }
        fs.max_freq = dup
    } else {
        fs.stacks[fs.max_freq]  = stack[:len(stack)-1]
    }
    return
}

func main() {
    fs := NewFreqStack()
    fs.push("5")
    fs.push("7")
    fs.push("5")
    fs.push("7")
    fs.push("4")
    fs.push("7")
    fmt.Printf("%+v\n", fs)
    fmt.Println(fs.pop())
    fmt.Println(fs.pop())
    fmt.Println(fs.pop())
    fmt.Println(fs.pop())
    fmt.Println(fs.pop())
    fmt.Println(fs.pop())
    fmt.Println(fs.pop())
}
