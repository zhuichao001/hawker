#include ""

int main(){
    int a[6]={6,4,5,9,7,3};
    SegmentTree st(a, 6, max, INT_MIN);
    int s = st.query_range(0,5);
    cout<<"max result:"<<s<<endl;

    SegmentTree st2(a, 6, sum, 0);
    int t = st2.query_range(0,5);
    cout<<"sum result:"<<t<<endl;
}
