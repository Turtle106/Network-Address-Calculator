#include <iostream>
#include <string>
#include <sstream>
#include <bitset>
#include "ipContainer.h"

using std::string;

string toString(unsigned long addr) {
    unsigned long mask = 255;
    unsigned long ip = addr;
    std::stringstream temp;

    for (int i = 3; i >= 0; i--) {
        temp << (ip >> (8 * i) & mask);

        if (i > 0) {
            temp << '.';
        }
    }

    return temp.str();
}

void printResults(Container IP, Container SUB) {
    unsigned long networkAddr = IP.fullIP & SUB.fullIP;
    unsigned long startAddr = networkAddr + 1;
    unsigned long broadcastAddr = (networkAddr | (~SUB.fullIP));
    unsigned long endAddr = broadcastAddr - 1;

    std::cout << "Network Address: " << toString(networkAddr) << std::endl;
    std::cout << "Network Scope: " << toString(startAddr) << " - " << toString(endAddr) << std::endl;
    std::cout << "Broadcast Address: " << toString(broadcastAddr) << std::endl;
    std::cout << "Address Classification: " << SUB.computeSubnet() << std::endl;;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Please enter 2 ip addresses in command-line execution" << std::endl;
        return 1;
    }

    string IP_STR = argv[1];
    string SUB_STR = argv[2];

    std::stringstream IP_SS(IP_STR);
    std::stringstream SUB_SS(SUB_STR);

    Container ipAdd = Container(IP_STR);
    Container subnet = Container(SUB_STR);

    printResults(ipAdd, subnet);

    return 0;
}
