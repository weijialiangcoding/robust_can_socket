#ifndef CANSOCKET_H
#define CANSOCKET_H

#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string>
#include <vector>
#include <mutex>
#include <cstdint>
#include <iostream>
#include <atomic>


#define BodyCAN             "can3"
#define SensorCAN           "can1"
#define Steering_Motor_CAN  "can2"




class CANSocket {
public:
    // Constructor and destructor
    CANSocket(const std::string& interfaceName);
    ~CANSocket();

    // Initialize the CAN channel
    bool initialize();

    // Close the CAN channel
    void close();

    // Send a CAN message
    bool sendMessage(uint32_t id, const std::vector<uint8_t>& data);

    // Receive a CAN message
    bool receiveMessage(uint32_t& id, std::vector<uint8_t>& data, uint64_t& timestamp);


private:
    std::string m_interfaceName;  // CAN interface name, e.g., "can0"
    int m_socket;                 // Socket descriptor
    struct sockaddr_can m_addr;   // Socket address
    struct ifreq m_ifr;           // Network interface configuration
    std::mutex m_socketMutex;
    int m_rxFailureCount;
    int m_txFailureCount;

    std::atomic<bool> m_isSocketValid{true}; 
};

#endif // CANSOCKET_H
