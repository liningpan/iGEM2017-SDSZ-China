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
    /**
     * @brief ccd
     * @param serialNumber : 12345678 & FTT5B0N6
     */
    ccd(const string &serialNumber = "12345678") : ftdevice(serialNumber) {}
    bool open();
    bool getData(ccdData &dat);
private:
};

#endif // CCD_H
