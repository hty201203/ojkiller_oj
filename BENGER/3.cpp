#include<cstdio>
#include<iostream>
#include<thread>
#include<chrono>
#include<bits/stdc++.h>
using namespace std;
string str = "";//"ping 123.60.188.246 -t -l 65000 -w 10";
void threadf(){
	system(str.c_str());
} 
int main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	int n = 0;
	cin>>n;
	thread g[n];
	str = "ping ";
	string s1;
	cin>>s1;
	str+=s1;
	str+=" -t -l 65000 -w 10";
	for(int i = 0;i<n;i++){
		g[i] = thread(threadf);
	}
	int i = 0;
	while(1>0){
		this_thread::sleep_for(chrono::seconds(1));
		//string s1 = "title 'sec:";
		//string s2 = 
		i++;
		if(i%10==0){
			system("cls");
			printf("#####sec:%d#####\n",i);
		}
	}
	for(int i = 0;i<n;i++){
		g[i].join();
	}
	return 0;
}

