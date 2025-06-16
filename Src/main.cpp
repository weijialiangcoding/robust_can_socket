#include "CANSocket.h"
#include "CANMessage.h"  
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <csignal>
#include <vector>
#include <algorithm>

constexpr int TX_MSGS_LEN = 3;
std::array<int, TX_MSGS_LEN> sampleTimes = {10, 20, 100}; // ms

std::atomic<bool> running{true};

std::array<uint32_t, 8> RX_IDS = {0x101, 0x102, 0x103, 0x201, 0x202, 0x203, 0x301, 0x302};

void printMessage(const CanMessage& msg) {
    std::cout << "[RECV] ID: 0x" << std::hex << msg.id << "  Data:";
    for (int i = 0; i < msg.dlc; ++i)
        std::cout << " " << std::hex << static_cast<int>(msg.data[i]);
    std::cout << std::dec << std::endl;
}

void sendLoop(CANSocket* socket) {
    std::array<std::chrono::steady_clock::time_point, TX_MSGS_LEN> nextSend;
    auto now = std::chrono::steady_clock::now();
    for (int i = 0; i < TX_MSGS_LEN; ++i) {
        nextSend[i] = now;
    }

    while (running) {
        now = std::chrono::steady_clock::now();
        std::chrono::nanoseconds minSleep = std::chrono::seconds(1);

        for (int i = 0; i < TX_MSGS_LEN; ++i) {
            if (now >= nextSend[i]) {
                uint32_t id = 0x100 + i;
                std::vector<uint8_t> data = {static_cast<uint8_t>(i), 2, 3, 4};

                if (!socket->sendMessage(id, data)) {
                    std::cerr << "[SEND] Failed to send ID: 0x" << std::hex << id << std::dec << std::endl;
                }

                nextSend[i] += std::chrono::milliseconds(sampleTimes[i]);
            }

            auto diff = nextSend[i] - now;
            if (diff < minSleep) minSleep = diff;
        }

        std::this_thread::sleep_for(minSleep);
    }
}

void recvLoop(CANSocket* socket) {

    uint32_t id;
    std::vector<uint8_t> data;
    uint64_t timestamp;

    while (running) {
        CanMessage msg;
        if (socket->receiveMessage(id,data,timestamp)) {
            if (std::find(RX_IDS.begin(), RX_IDS.end(), msg.id) != RX_IDS.end()) {
                printMessage(msg);
            }
        } else if (errno == ENOBUFS || errno == ENETDOWN) {
            std::cerr << "[RECV] Socket error, restarting...\n";
            socket->close();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            socket->initialize();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void signalHandler(int) {
    running = false;
    std::cout << "Stopping...\n";
}

int main() {
    std::signal(SIGINT, signalHandler);

    CANSocket socket("vcan0");
    if (!socket.initialize()) {
        std::cerr << "Failed to initialize CAN interface\n";
        return 1;
    }

    std::thread tx(sendLoop, &socket);
    std::thread rx(recvLoop, &socket);

    std::cout << "Running... Press Enter to exit.\n";
    std::cin.get();
    running = false;

    tx.join();
    rx.join();
    return 0;
}
