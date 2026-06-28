#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <string>
#include <vector>

class SerialPort
{
public:

    SerialPort();

    ~SerialPort();

    bool open(
        const std::string& device,
        int baudrate);

    void close();

    void flush();

    bool isOpen() const;

    bool write(
        const std::vector<uint8_t>& data);

    bool read(
        std::vector<uint8_t>& data,
        int timeoutMs = 1000);

    bool readFrame(
        std::vector<uint8_t>& data,
        int firstTimeoutMs = 1000,
        int interByteTimeoutMs = 20);

    bool writeRead(
        const std::vector<uint8_t>& tx,
        std::vector<uint8_t>& rx,
        int timeoutMs = 1000);

private:

    int m_fd;
};

#endif