#include<iostream>
#include<vector>
using namespace std;

vector<int> ss(vector<int> v){
    for(int i=0;i<v.size()-1;i++){
        int m = i;
        for(int j=i+1;j<v.size();j++){
            if(v[j] < v[m] ) m = j;
        }

        if(m != i){
            swap(v[m], v[i]);
        }
    }
    return v;
}

int main(){
    vector<int> v;
    int n = 5;
    cout << "Enter 5 numbers: ";
    for(int i=0;i<n;i++){
        int temp;
        cin >> temp;
        v.push_back(temp);
    }
     v = ss(v);
    cout << "sorted output: ";
    for (auto it: v){
        cout << it << " ";
    }
    cout << endl;
    return 0;
}