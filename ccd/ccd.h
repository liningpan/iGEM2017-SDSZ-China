#ifndef CCD_H
#define CCD_H
#include "ftd2xx.h"
#include "ftdevice.h"
#include <string>
using namespace std;
struct ccdData
{
    unsigned short dat[3648];
    unsigned short &operator[](int p){return dat[p];}
};

class ccd : public ftdevice
{
public:
    ccd(const string &serialNumber = "FTT5B0N6") : ftdevice(serialNumber) {}
    bool open();
    bool getData(ccdData &dat);
private:
};

#endif // CCD_H
