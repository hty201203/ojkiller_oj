#include <iostream>
#include <iphlpapi.h>
#include<windows.h>
 
int main1() {
    MIB_IF_ROW2 ifRow;
    ifRow.InterfaceIndex = 0; // 需要获取哪个网络接口的使用率，这里0表示第一个接口
    ifRow.dwFamily = AF_INET; // IPv4
    ifRow.InterfaceLuid = 0; // 接口的LUID
 
    if (GetIfEntry2(&ifRow) == NO_ERROR) {
        ULONGLONG sent = ifRow.OutOctets; // 发送的字节数
        ULONGLONG received = ifRow.InOctets; // 接收的字节数
 
        // 假设过去1秒内统计的数据是新的
        ULONGLONG sentDiff = sent - ifRow.OutOctets;
        ULONGLONG receivedDiff = received - ifRow.InOctets;
 
        double sentPerSec = sentDiff * 8 / 1024.0 / 1024.0; // 转换为MB/s
        double receivedPerSec = receivedDiff * 8 / 1024.0 / 1024.0; // 转换为MB/s
 
        std::cout << "网络发送速率: " << sentPerSec << " MB/s" << std::endl;
        std::cout << "网络接收速率: " << receivedPerSec << " MB/s" << std::endl;
    } else {
        std::cerr << "获取网络接口信息失败" << std::endl;
    }
 
    return 0;
}
