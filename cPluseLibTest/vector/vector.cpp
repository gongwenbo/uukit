#include<vector>
#include<iostream>
#include<algorithm>

#include<string>
#include<iterator>
#include<array>
using namespace std;

int testVec(char* a){
	
	vector<int> v({2,3,7});
	for(const auto&value:v){
		
		cout<<value<<endl;
	}
	
	vector<int> destination(8);
	reverse_copy(begin(v),end(v),begin(destination));
	for(const auto&value:destination){
		cout<<value<<endl;
	}
	return 0;
	
}

int testArray(char* a){
	
	array<int,3> ia1={23,12,123};
	array<string,3> sa1={to_string(007),"like"};
	sort(ia1.begin(),ia1.end());
	for(const auto& value:ia1){
		cout<<value<<endl;
				
	}
	for(const auto& value:sa1){
		cout<<value<<endl;
				
	}		
	return 0;
}

int main(int argc,char* argv[]){
	
	char test[40]="asf";
	//testVec(test);
	testArray(test);
	return 0;
	
}