#include "device/SerialPort.h"

#include <fcntl.h>
#include <poll.h>
#include <termios.h>
#include <unistd.h>

#include <chrono>
#include <thread>

#include "Logger.h"

SerialPort::SerialPort()
{
    m_fd = -1;
}

SerialPort::~SerialPort()
{
    close();
}

bool SerialPort::open(
    const std::string& device,
    int baudrate)
{
    m_fd = ::open(
        device.c_str(),
        O_RDWR | O_NOCTTY | O_SYNC);

    if (m_fd < 0)
    {
        Logger::error("No se pudo abrir " + device);
        return false;
    }

    termios tty{};

    if (tcgetattr(m_fd, &tty) != 0)
    {
        Logger::error("tcgetattr() falló.");
        close();
        return false;
    }

    cfmakeraw(&tty);

    speed_t speed = B230400;

    if (baudrate == 115200)
        speed = B115200;

    cfsetispeed(&tty, speed);
    cfsetospeed(&tty, speed);

    tty.c_cflag |= (CLOCAL | CREAD);

    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;

    tty.c_cc[VMIN]  = 0;
    tty.c_cc[VTIME] = 0;

    if (tcsetattr(
            m_fd,
            TCSANOW,
            &tty) != 0)
    {
        Logger::error("tcsetattr() falló.");
        close();
        return false;
    }

    tcflush(
        m_fd,
        TCIOFLUSH);

    Logger::info(
        "Puerto serie abierto correctamente.");

    return true;
}

void SerialPort::close()
{
    if (m_fd >= 0)
    {
        ::close(m_fd);
        m_fd = -1;
    }
}

void SerialPort::flush()
{
    if (m_fd >= 0)
    {
        tcflush(
            m_fd,
            TCIOFLUSH);
    }
}

bool SerialPort::isOpen() const
{
    return m_fd >= 0;
}

bool SerialPort::write(
    const std::vector<uint8_t>& data)
{
    if (m_fd < 0)
        return false;

    ssize_t written =
        ::write(
            m_fd,
            data.data(),
            data.size());

    tcdrain(m_fd);

    return written ==
        static_cast<ssize_t>(data.size());
}

bool SerialPort::read(
    std::vector<uint8_t>& data,
    int timeoutMs)
{
    if (m_fd < 0)
        return false;

    pollfd pfd;

    pfd.fd = m_fd;
    pfd.events = POLLIN;

    if (poll(
            &pfd,
            1,
            timeoutMs) <= 0)
    {
        return false;
    }

    uint8_t buffer[512];

    int n =
        ::read(
            m_fd,
            buffer,
            sizeof(buffer));

    if (n <= 0)
        return false;

    data.assign(
        buffer,
        buffer + n);

    return true;
}

bool SerialPort::readFrame(
    std::vector<uint8_t>& data,
    int firstTimeoutMs,
    int interByteTimeoutMs)
{
    data.clear();

    if (m_fd < 0)
        return false;

    pollfd pfd;

    pfd.fd = m_fd;
    pfd.events = POLLIN;

    if (poll(
            &pfd,
            1,
            firstTimeoutMs) <= 0)
    {
        return false;
    }

    while (true)
    {
        uint8_t buffer[512];

        int n =
            ::read(
                m_fd,
                buffer,
                sizeof(buffer));

        if (n > 0)
        {
            data.insert(
                data.end(),
                buffer,
                buffer + n);
        }

        if (poll(
                &pfd,
                1,
                interByteTimeoutMs) <= 0)
        {
            break;
        }
    }

    return !data.empty();
}

bool SerialPort::writeRead(
    const std::vector<uint8_t>& tx,
    std::vector<uint8_t>& rx,
    int timeoutMs)
{
    if (!write(tx))
        return false;

    std::this_thread::sleep_for(
        std::chrono::milliseconds(20));

    return readFrame(
        rx,
        timeoutMs,
        20);
}