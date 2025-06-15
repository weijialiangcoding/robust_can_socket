# robust_can_socket

CANSocket - Lightweight SocketCAN Abstraction for Modern C++ Projects

A minimal and robust C++ wrapper around Linux SocketCAN with built-in error handling, thread safety, and automatic recovery for CAN bus off and I/O failures.

    Ideal for embedded Linux, robotics, automotive gateways, or quick CAN-based tooling without pulling in heavy dependencies.

✨ Features

    ✅ Easy-to-use C++ interface (RAII-compliant)

    🔁 Automatic socket reinitialization on failure (e.g., Bus-Off, ENETDOWN, ENOBUFS)

    🧵 Thread-safe send/receive with std::mutex
ing I/O with graceful EAGAIN handling

    🛑 Non-block
    📦 Lightweight and header-only style (single .cpp/.h)

    🔧 Tested on x86 Linux


🛠️ Development Roadmap (To-do)

Add vcan-based virtual test environment (no hardware required)

Write automated test scripts for validation

Provide a complete main.cpp example for getting started

Share a standalone C++ demo using this library (without ROS2 dependencies)

Share a ROS2-CAN interface example, to help integrate with autonomous driving or robotics projects

Refactor the structure to support use as a Git submodule for easy integration

Future plan: Use this library as a host-side platform for STM32 firmware upgrade over CAN
