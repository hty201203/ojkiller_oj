#include <iostream>
#include <iphlpapi.h>
#include<windows.h>
 
int main1() {
    MIB_IF_ROW2 ifRow;
    ifRow.InterfaceIndex = 0; // ��Ҫ��ȡ�ĸ�����ӿڵ�ʹ���ʣ�����0��ʾ��һ���ӿ�
    ifRow.dwFamily = AF_INET; // IPv4
    ifRow.InterfaceLuid = 0; // �ӿڵ�LUID
 
    if (GetIfEntry2(&ifRow) == NO_ERROR) {
        ULONGLONG sent = ifRow.OutOctets; // ���͵��ֽ���
        ULONGLONG received = ifRow.InOctets; // ���յ��ֽ���
 
        // �����ȥ1����ͳ�Ƶ��������µ�
        ULONGLONG sentDiff = sent - ifRow.OutOctets;
        ULONGLONG receivedDiff = received - ifRow.InOctets;
 
        double sentPerSec = sentDiff * 8 / 1024.0 / 1024.0; // ת��ΪMB/s
        double receivedPerSec = receivedDiff * 8 / 1024.0 / 1024.0; // ת��ΪMB/s
 
        std::cout << "���緢������: " << sentPerSec << " MB/s" << std::endl;
        std::cout << "�����������: " << receivedPerSec << " MB/s" << std::endl;
    } else {
        std::cerr << "��ȡ����ӿ���Ϣʧ��" << std::endl;
    }
 
    return 0;
}
