#ifndef CCD_H
#define CCD_H
#include <ftd2xx.h>
#include <string>
using namespace std;
struct ccdData
{
    unsigned short dat[3648];
};

class ccd
{
public:
    string serialNumber = "12345678";
    ccd();
    FT_HANDLE handle;
    bool open();
    void write(char *str, int size);
    ccdData read();
    ccdData getData();
private:
    void deviceList();
};

#endif // CCD_H
