#include<string>
#include<string_view>
#include<queue>
#include<tuple>
#include<iostream>


void reverse_statement(const std::string &input, std::string &res){
    std::deque<std::tuple<int,int>> stack;
    for(int start=0,end=0;end<=input.size();++end){
        if((input[end]==' '|| input[end]==0)&& input[start]!=' '){
            stack.push_front(std::tuple<int,int>(start, end));
            start=end;
        }else if(input[start]==' ') {
            start=end;
        }
    }

    res.clear();
    while(!stack.empty()){
        auto [start, end] = stack.front();
        stack.pop_front();
        res += std::string_view(input.c_str()+start, end-start);
        res += " ";
    }
}

int main(){
    std::string res;
    std::string input="student. a am I";
    reverse_statement(input, res);
    std::cout << res << std::endl;
    return 0;
}
