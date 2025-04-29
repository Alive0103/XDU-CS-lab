#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
using namespace std;

int main()
{
    int fd = open("/dev/edu", O_RDONLY);
    if (fd == -1)
    {
        cerr << "can not open" << endl;
        return -1;
    }
    int ret = ioctl(fd, 0, 10);
    cout << "ioctl write1: " << 10 << endl;
    sleep(1);
    ret = ioctl(fd,1,0);
    cout << "ioctl read1: " << ret << endl;
    ret = ioctl(fd, 0, 5);
    cout << "ioctl write2: " << 5 << endl;
    sleep(1);
    ret = ioctl(fd,1,0);
    cout << "ioctl read2: " << ret << endl;
    close(fd);
}