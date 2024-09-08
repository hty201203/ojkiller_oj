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
    // ��ȡCPUƵ��
    QueryPerformanceFrequency(&freq);
    // ��һ�ζ�ȡCPUʱ��
    GetSystemTimes(&idleTime, &kernelTime, &userTime);
    SystemTimeToFileTime(&idleTime, (FILETIME*)&idleTimeStart);
    SystemTimeToFileTime(&kernelTime, (FILETIME*)&kernelTimeStart);
    SystemTimeToFileTime(&userTime, (FILETIME*)&userTimeStart);
    // ģ��һ�κ�ʱ�������Ա��ڼ���CPUʹ����
    this_thread::sleep_for(chrono::seconds(1));
    // �ٴζ�ȡCPUʱ��
    GetSystemTimes(&idleTime, &kernelTime, &userTime);
    LARGE_INTEGER idleTimeEnd, kernelTimeEnd, userTimeEnd;
    SystemTimeToFileTime(&idleTime, (FILETIME*)&idleTimeEnd);
    SystemTimeToFileTime(&kernelTime, (FILETIME*)&kernelTimeEnd);
    SystemTimeToFileTime(&userTime, (FILETIME*)&userTimeEnd);
    // ����CPUʱ���
    LONGLONG idleDiff = (idleTimeEnd.QuadPart - idleTimeStart.QuadPart);
    LONGLONG kernelDiff = (kernelTimeEnd.QuadPart - kernelTimeStart.QuadPart);
    LONGLONG userDiff = (userTimeEnd.QuadPart - userTimeStart.QuadPart);
    // ����CPUռ����
    double cpuUsage = (kernelDiff + userDiff - idleDiff) / (freq.QuadPart * 1000000.0);
    std::cout << "CPU Usage: " << cpuUsage << "%" << std::endl;
    return 0;
}
int main(){
	while(1>0) main1();
}
