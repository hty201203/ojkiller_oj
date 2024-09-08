#include <Windows.h>
#include <iostream>
#include<cstdio>
#include<thread>
#include<chrono>
#include<bits/stdc++.h>
int main1() {
    FILETIME idleTime, kernelTime, userTime;
    LARGE_INTEGER idleTimeStart, kernelTimeStart, userTimeStart;
    LARGE_INTEGER freq;
    // 获取CPU频率
    QueryPerformanceFrequency(&freq);
    // 第一次读取CPU时间
    GetSystemTimes(&idleTime, &kernelTime, &userTime);
    SystemTimeToFileTime(&idleTime, (FILETIME*)&idleTimeStart);
    SystemTimeToFileTime(&kernelTime, (FILETIME*)&kernelTimeStart);
    SystemTimeToFileTime(&userTime, (FILETIME*)&userTimeStart);
    // 模拟一段耗时操作，以便于计算CPU使用率
    this_thread::sleep_for(chrono::seconds(1));
    // 再次读取CPU时间
    GetSystemTimes(&idleTime, &kernelTime, &userTime);
    LARGE_INTEGER idleTimeEnd, kernelTimeEnd, userTimeEnd;
    SystemTimeToFileTime(&idleTime, (FILETIME*)&idleTimeEnd);
    SystemTimeToFileTime(&kernelTime, (FILETIME*)&kernelTimeEnd);
    SystemTimeToFileTime(&userTime, (FILETIME*)&userTimeEnd);
    // 计算CPU时间差
    LONGLONG idleDiff = (idleTimeEnd.QuadPart - idleTimeStart.QuadPart);
    LONGLONG kernelDiff = (kernelTimeEnd.QuadPart - kernelTimeStart.QuadPart);
    LONGLONG userDiff = (userTimeEnd.QuadPart - userTimeStart.QuadPart);
    // 计算CPU占用率
    double cpuUsage = (kernelDiff + userDiff - idleDiff) / (freq.QuadPart * 1000000.0);
    std::cout << "CPU Usage: " << cpuUsage << "%" << std::endl;
    return 0;
}
int main(){
	while(1>0) main1();
}
