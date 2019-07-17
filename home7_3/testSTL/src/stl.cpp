#include "stl.h"
void testMap(){
	//std::map<string,uint32_t> class_room;
	std::multimap<string,uint32_t> class_room;
	for (int i=0;i<10;i++){
		class_room.emplace("name"+to_string(i),i);
	}
	class_room.insert(pair<string,uint32_t>("name2",100));
	for(auto& iter:class_room){
		cout<<iter.first<<" "<<iter.second<<"\n";
	}
	cout<<"size:"<<class_room.size()<<"\n";
}

void testDeque(){
	std::deque<uint64_t> buf;
	auto start_d=high_resolution_clock::now();
	for(int i=0;i<1000;i++){
		buf.emplace_back(i*i);
	}
	auto end_d=high_resolution_clock::now();
	cout<<"deque excute time:"<<duration_cast<microseconds>(start_d-end_d).count()<<"\n";
	
/*std::vector test*/
	std::vector<uint64_t> vbuf;
	auto start_v=high_resolution_clock::now();
	for(int i=0;i<1000;i++){
		vbuf.emplace_back(i*i);
	}
	auto end_v=high_resolution_clock::now();
	cout<<"vector excute time:"<<duration_cast<microseconds>(start_v-end_v).count()<<"\n";
	
/*find element*/
	auto start_df=high_resolution_clock::now();
	auto tare=buf.at(500);
	//if(tar!=buf.end())
		cout<<tare<<"\n";
	auto end_df=high_resolution_clock::now();
	cout<<"deque find time:"<<duration_cast<microseconds>(start_df-end_df).count()<<"\n";
	
	auto start_vf=high_resolution_clock::now();
	auto tar=vbuf.at(500);
	//if(tar!=vbuf.end())
		cout<<tar<<"\n";
	auto end_vd=high_resolution_clock::now();
	cout<<"deque find time:"<<duration_cast<microseconds>(start_vf-end_vd).count()<<"\n";
	
/*delete element*/
	auto start_dd=high_resolution_clock::now();
	buf.erase(buf.begin()+500,buf.end());
	auto stop_dd=high_resolution_clock::now();
	cout<<"deque delete:"<<duration_cast<microseconds>(start_dd-stop_dd).count()<<"\n";
	
	auto start_vd=high_resolution_clock::now();
	vbuf.erase(vbuf.begin()+500,vbuf.end());
	auto stop_vd=high_resolution_clock::now();
	cout<<"vector delete:"<<duration_cast<microseconds>(start_vd-stop_vd).count()<<"\n";	
		
}

void testSet(){
	int i=100;
	set<string> set_test;
	for(;i>0;i--){
		set_test.emplace("name"+to_string(i));
	}
	set_test.emplace("name30");
	for(auto& iter:set_test){
		cout<<iter<<"\n";
	}
}

void testQueue(){
	queue<uint32_t> test_que;
	for(int i=0;i<10;i++){
		test_que.emplace(i);
	}
	while(!test_que.empty()){
		cout<<"test queue"<<test_que.front()<<"\n";
		test_que.pop();
	}
	
	
}

void testStack(){
	stack<string> test_stack;
	int i=10;
	while(i--){
		test_stack.emplace(to_string(i));
	}
	while(!test_stack.empty()){
		cout<<"stack "<<test_stack.top()<<"\n";
		test_stack.pop();
	}
	
	
}

void testAlgorithm(){
	cout<<"test algorithm\n";
	deque<uint32_t> nums;
	for(int i=10;i>0;i--){
		nums.emplace_back(i);
	}
	nums.emplace_back(8);
	sort(nums.begin(),nums.end());
	auto del_node=unique(nums.begin(),nums.end());
	nums.resize(del_node-nums.begin());
	//reverse(nums.begin(),nums.end());
	for(auto &index:nums){
		cout<<index<<"\n";
	}
	cout<<"count"<<count_if(nums.begin(),nums.end(),[=](uint32_t e){
		if(e%2==0)
			return 1;
		else 
			return 0;
	})<<"\n";
	
	auto pos=find_if(nums.begin(),nums.end(),[=](uint32_t e){
		if(e==8)
			return 1;
		else 
			return 0;
	});
	if(pos!=nums.end())
		cout<<*pos<<"\n";


	replace_if(nums.begin(),nums.end(),[=](uint32_t i){
		if(i%2==0)
			return 1;
		else
			return 0;
	},0);
	sort(nums.begin(),nums.end());
	unique(nums.begin(),nums.end());
	for(auto &i:nums){
		cout<<i<<"\n";
	}
	auto ma_ele=max_element(nums.begin(),nums.end());
	cout<<"max:"<<*ma_ele<<"\n";
	
	deque<uint32_t> stu1;
	stu1.emplace_back(10);
	stu1.emplace_back(12);
	stu1.emplace_back(121);
	
	deque<uint32_t> stu2;
	stu2.emplace_back(11);
	stu2.emplace_back(12);
	auto ind=search(stu1.begin(),stu1.end(),stu2.begin(),stu2.end());
	if(ind!=stu1.end())
		cout<<ind-stu1.begin()<<"\n";
	else{
		cout<<"no find\n";
	}
		
}


