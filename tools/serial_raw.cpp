#include <fcntl.h>
#include <poll.h>
#include <termios.h>
#include <unistd.h>

#include <cstdio>
#include <cstring>
#include <iostream>

static void dump(const uint8_t *buf, int n)
{
    for (int i = 0; i < n; i++)
        printf("%02X ", buf[i]);

    printf("\n");
}

int main()
{
    const char *port =
        "/dev/serial/by-id/usb-1a86_USB2.0-Serial-if00-port0";

    int fd = open(port, O_RDWR | O_NOCTTY);

    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    termios tty{};

    tcgetattr(fd, &tty);

    cfmakeraw(&tty);

    cfsetispeed(&tty, B230400);
    cfsetospeed(&tty, B230400);

    tty.c_cflag |= (CLOCAL | CREAD);

    tcsetattr(fd, TCSANOW, &tty);

    tcflush(fd, TCIOFLUSH);

    uint8_t reset[] =
    {
        0x61,
        0x00,
        0x07,
        0x00,
        0x34,
        0x05,
        0x00,
        0x00,
        0x0F,
        0x00,
        0x00
    };

    printf("TX:\n");

    dump(reset, sizeof(reset));

    write(fd, reset, sizeof(reset));

    tcdrain(fd);

    pollfd pfd;

    pfd.fd = fd;
    pfd.events = POLLIN;

    printf("\nEsperando datos...\n\n");

    for (int i = 0; i < 20; i++)
    {
        if (poll(&pfd, 1, 250) <= 0)
            continue;

        uint8_t buffer[512];

        int n =
            read(
                fd,
                buffer,
                sizeof(buffer));

        if (n <= 0)
            continue;

        printf("READ %d bytes:\n", n);

        dump(buffer, n);

        printf("\n");
    }

    close(fd);

    return 0;
}