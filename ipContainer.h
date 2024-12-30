
#ifndef IP_CONTAINER
#define IP_CONTAINER

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <bitset>

class Container {
    std::vector<unsigned long> segments;
public:
    std::string seg;
    unsigned long fullIP;

    Container() = default;

    Container(std::string IP) {
        std::stringstream ss(IP);
    
        while(std::getline(ss, seg, '.')) {
            segments.push_back(stoul(seg));
        }

        if (segments.size() != 4) {
            throw std::exception();
        }

        fullIP = segments[3];

        for (int i = 0; i < 3; i++) {
            fullIP += (segments[i] << (24 - (8 * i)));
        }
    }

    void repack() {
        for (int i = 0; i < 3; i++) {
            segments[i] = ((fullIP >> (24 - (8 * i))) & 255);
        }
    }

    std::string computeSubnet() {
        unsigned int count = 0;
        unsigned long temp = (fullIP << 32); 

        while (temp > 0) {
            temp <<= 1;
            count++;
        }

        return (count <= 16) ? ((count <= 8) ? "A" : "B") : ((count <= 24) ? "C" : "D");
    }
};

#endif
