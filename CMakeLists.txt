cmake_minimum_required(VERSION 3.16)

project(AMBEHub VERSION 0.15.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/bin)

include_directories(include)

set(COMMON_SOURCES

    #
    # Core
    #

    src/Logger.cpp
    src/Config.cpp

    #
    # Network
    #

    src/network/SocketUDP.cpp

    #
    # Protocol
    #

    src/protocol/Packet.cpp
    src/protocol/PacketDispatcher.cpp
    src/protocol/PacketSerializer.cpp
    src/protocol/PacketSerializer.cpp

    src/protocol/AMBEFrame.cpp
    src/protocol/AMBE3000Protocol.cpp
    src/protocol/DV3KResponse.cpp

    #
    # Session
    #

    src/session/Session.cpp
    src/session/SessionManager.cpp

    #
    # Core
    #

    src/core/AMBEHubCore.cpp

    #
    # Devices
    #

    src/device/DeviceManager.cpp
    src/device/DummyDevice.cpp
    src/device/SerialPort.cpp
    src/device/AMBE3000Device.cpp
)

#
# Servidor
#

add_executable(ambehub

    src/main.cpp

    src/server/AMBEHubServer.cpp

    src/network/UDPServer.cpp

    ${COMMON_SOURCES}
)

#
# Cliente
#

add_executable(ambehub_client

    src/client/main.cpp

    src/client/AMBEHubClient.cpp

    ${COMMON_SOURCES}
)

#
# Diagnóstico
#

add_executable(ambe_diag

    tools/ambe_diag.cpp

    ${COMMON_SOURCES}
)