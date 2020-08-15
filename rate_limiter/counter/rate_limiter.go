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
    Current int32
    Interval int32
}


func NewCountLimiter(num int32, ms int32) (limiter *CountLimiter) {
    limiter = &CountLimiter{
        Limit: num,
        Current: 0,
        Interval: ms, //MiliSecond
    }
    return
}


func (c *CountLimiter)Acquire() bool {
    current := c.Current
    if current > c.Limit {
        return false
    }

    ok := atomic.CompareAndSwapInt32(&c.Current, current, current+1)
    return ok
}


func (c *CountLimiter)Run() {
    dura := time.Duration(c.Interval)*time.Millisecond
    ticker := time.NewTicker(dura)    
    for {
        select {
            case <- ticker.C:
            c.Current = 0
            fmt.Println("@Rest")
        }
    }
}


func consume(limiter *CountLimiter) {
    reader := bufio.NewReader(os.Stdin)
    for {
        reader.ReadString('\n')
        ok := limiter.Acquire()
        fmt.Println(ok)
    }
}


func main(){
    limiter := NewCountLimiter(2, 3000);
    go limiter.Run()
    consume(limiter)
}
