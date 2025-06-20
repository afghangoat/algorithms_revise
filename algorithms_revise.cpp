#include <algorithm>
#include <iostream>
#include <vector>
#include <limits.h>
//For c++20

//O(log(n+1))
bool BinarySearch(std::vector<int>& container, int value){
    int low=0;
    int high=container.size()-1;
    while(low<=high){
        int mid = (low + high)/2;
        if (value == container[mid]){
            return true;
        }else if (value > container[mid]){//X on right
            low = mid + 1;
        }else{//X on left
            high = mid - 1;
        }
        
    }
    return false;
}

//BFS: O(n^2) <- if DAG or every weight is 1, O(n+m) with edge list.
template <typename T, template <typename, typename> class Container>
std::ostream& operator<<(std::ostream& os, const Container<T, std::allocator<T>>& container) {
    for (auto it = container.begin(); it != container.end(); ++it) {
        os << *it;
        if (std::next(it) != container.end()){
            os << ", ";
        }
    }
    os <<std::endl;
    return os;
}

//O(n)
int MaxSummedInterval(std::vector<int>& input, bool debug){
    int result=INT_MIN;
    std::vector<int> L;
    L.push_back(input[0]); //L[0] Is fixed
    
    for(int i=1;i<input.size();i++){
        int new_l=L[i-1]+input[i];
        if(input[i]>new_l){
            new_l=input[i];
        }
        L.push_back(new_l);
    }
    
    if(debug==true){ //Print table
        std::cout << "--------------" << std::endl;
        std::cout << "A: |" << input << std::endl;
        std::cout << "L: |" << L << std::endl;
        std::cout << "--------------" << std::endl;
    }
    for(int i=0;i<L.size();i++){
        if(result<L[i]){
            result=L[i];
        }
    }
    return result;
}

//O(n^2)
std::vector<int> MaxIncreasingInterval(std::vector<int>& input,bool debug){
    std::vector<int> result;
    std::vector<int> prev;
    std::vector<int> L;
    
    
    for(size_t i=0;i<input.size();i++){
        int new_l=1;
        int new_prev=-1;
        for(size_t j=0;j<i;j++){
            if(input[j]<input[i]){
                new_l++;
                new_prev=j;
            }
        }
        prev.push_back(new_prev);
        L.push_back(new_l);
        
    }
    //max find
    int last_prev=-1;
    int old_l=0;
    int starter=0;
    for(size_t i=0;i<L.size();i++){
        if(L[i]>old_l){
            old_l=L[i];
            starter=input[i];
            last_prev=prev[i];
        }
    }
    last_prev-=1;
    
    result.insert(result.begin(), starter);
    do{
        result.insert(result.begin(), input[last_prev]);
        last_prev=prev[last_prev];
    } while(last_prev!=-1);
    
    if(debug==true){ //Print table
        std::cout << "--------------" << std::endl;
        std::cout << "Input: |" << input << std::endl;
        std::cout << "Lengt: |" << L << std::endl;
        std::cout << "Prev : |" << prev << std::endl;
        std::cout << "--------------" << std::endl;
    }
    
    return result;
}

//Topologic sort: O(n+m)

//Binsort best case: O(n+k) Data amount and bucket count.
//But worst case O(n^2)
template <typename T, template <typename, typename> class Container>
void BinSort(Container<T, std::allocator<T>>& input) {
    if (input.empty()){
        return;
    }

    // Find the maximum element to know how many bins we need
    T max_val = *std::max_element(input.begin(), input.end());

    // Create bins
    std::vector<std::vector<T>> bins(static_cast<size_t>(max_val) + 1);

    // Distribute elements into bins
    for (const T& val : input) {
        bins[val].push_back(val);
    }

    // Collect sorted elements
    size_t index = 0;
    for (const auto& bin : bins) {
        for (const T& val : bin) {
            input[index++] = val;
        }
    }
}

template <typename T>
bool greater_than(T a, T b){
    if(a>b){
        return true;
    }
    return false;
}

template <typename T>
bool lesser_than(T a, T b){
    if(a<b){
        return true;
    }
    return false;
}
//Full merge sort is: O(n*log(n))
//Basic merge is: O(n+m)
template <typename Container, typename Pred>
Container Merge(const Container& container1, const Container& container2, Pred p) {
    Container result;

    auto it1 = container1.begin();
    auto it2 = container2.begin();

    while (it1 != container1.end() && it2 != container2.end()) {
        if (p(*it1,*it2)) {
            result.push_back(*it1++);
        } else {
            result.push_back(*it2++);
        }
    }
    
    //Remaining shall be inserted after
    result.insert(result.end(), it1, container1.end());
    result.insert(result.end(), it2, container2.end());
    return result;
}

template <typename T,template <typename, typename> class Container, typename Pred>
//The pivot gets returned.
int Partition(Container<T, std::allocator<T>>& input, int start_i, int end_i, Pred p){
    T pivot=input[end_i];
    int i=start_i-1;
    if(start_i==0){
    }
    for(int j=start_i;j<=end_i-1;++j){
        if(p(input[j], pivot)){
            //The i only moves if criteria met.
            i++;
            T temp = input[i];
            input[i]=input[j];
            input[j]=temp;
        }
    }
    i++;
    T temp = input[i];
    input[i]=input[end_i];
    input[end_i]=temp;
    
    return i;
}

//O(n*log(n))
template <typename T,template <typename, typename> class Container, typename Pred>
void QSort(Container<T, std::allocator<T>>& input, int start_i, int end_i, Pred p){
    if(end_i<=start_i){
        return;
    }
    int pivot = Partition(input,start_i,end_i,p);
    QSort(input,start_i,pivot-1,p);
    QSort(input,pivot+1,end_i,p);
}

int main() {
    
    std::vector<int> a={3,5,5,6};
    std::vector<int> b={1,2,3,4};
    
    std::vector<int> d={2,4,6,7,23,1,4,67,3};
    int start=0;
    QSort(d,start,d.size()-1,greater_than<int>);
    std::cout << d << " Made with Q sort." << std::endl;
    
    std::vector<int> c=Merge(a,b,lesser_than<int>);
    std::cout << c << " Made with merge sort." << std::endl;
    
    std::vector<int> e={9,5,2,8,7,3,1,6,4};
    std::cout << MaxIncreasingInterval(e,true);
    
    std::vector<int> f={-2,1,-3,4,-1,2,1,-5,4};
    std::cout << MaxSummedInterval(f,true);
	
	std::vector<int> for_search = {1,2,3,4,5,6,7};
    std::cout << BinarySearch(for_search,5);

    return 0;
}