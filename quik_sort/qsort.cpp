#include <vector> 
#include <algorithm> 
#include <iostream> 
#include <iterator> 
#include <forward_list> 


template <class It> 
void quicksort(It first, It last) { 
    if(first == last){
        return; 
    }
    auto pivot = *std::next(first, std::distance(first, last)/2);
    It mid1 = std::partition(first, last, [pivot](const auto &em){return em<pivot;});
    It mid2 = std::partition(first, last, [pivot](const auto &em){return !(pivot<em);});
    quicksort(first, mid1); 
    quicksort(mid2, last); 
}

void test1(){
    std::vector<int> v = {0,1,2,3,4,5,6,7,8,9}; 
    std::cout << "Original vector:\n "; 
    for(int elem : v) std::cout << elem << ' '; 
    auto it = std::partition(v.begin(), v.end(), [](int i){return i % 2 == 0;}); 

    std::cout << "\nPartitioned vector:\n "; 
    std::copy(std::begin(v), it, std::ostream_iterator<int>(std::cout, " ")); 
    std::cout << " * "; 
    std::copy(it, std::end(v), std::ostream_iterator<int>(std::cout, " ")); 
}

void test2(){
    std::forward_list<int> fl = {1, 30, -4, 3, 5, -4, 1, 6, -8, 2, -5, 64, 1, 92}; 
    std::cout << "\nUnsorted "; 
    for(int n : fl) std::cout << n << ' '; 
    std::cout << '\n'; 
    quicksort(std::begin(fl), std::end(fl)); 

    std::cout << "Sorted using quicksort:\n" ;
    for(int fi : fl) std::cout << fi << ' '; 
    std::cout << '\n'; 
}

int main() {
    test1();
    std::cout << "\n-----------------------\n";
    test2();
    return 0;
}
