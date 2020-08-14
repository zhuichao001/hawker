package main

import(
    "time"
    "fmt"
    "os"
    "bufio"
    "sync/atomic"
)


type CountLimiter struct {
    Limit int32
    Rest  int32
    Interval int32
}


func NewCountLimiter(num int32, ms int32) (limiter *CountLimiter) {
    //Rate: num*1000/ms
    limiter = &CountLimiter{
        Limit: num,
        Rest: num,
        Interval: ms, //MiliSecond
    }
    return
}


func (c *CountLimiter)Acquire(num int32) bool {
    for i:=0; i<3; i+=1 {
        rest := c.Rest
        if rest < num {
            return false
        }

        ok := atomic.CompareAndSwapInt32(&c.Rest, rest, rest-num)
        if ok {
            return true
        }
    }
    return false
}


func (c *CountLimiter)Run() {
    dura := time.Duration(c.Interval)*time.Millisecond
    ticker := time.NewTicker(dura)    
    for {
        select {
            case <- ticker.C:
            c.Rest = c.Limit
            fmt.Println("@Rest")
        }
    }
}


func consume(limiter *CountLimiter) {
    reader := bufio.NewReader(os.Stdin)
    for {
        reader.ReadString('\n')
        ok := limiter.Acquire(1)
        fmt.Println(ok)
    }
}


func main(){
    limiter := NewCountLimiter(2, 3000);
    go limiter.Run()
    consume(limiter)
}
