#pragma once

#include <vector>
#include <string>
#include <memory>
#include "IData.h"
namespace rf
{


enum class PixelFormatType: int
{
        Unknown             = 0x00,
        // mono formats
        Mono8               =  0x01,  // Monochrome, 8 bits (PFNC:Mono8)
        Mono10 ,               // Monochrome, 10 bits in 16 bits (PFNC:Mono10)
        Mono10p,  // Monochrome, 10 bits in 16 bits (PFNC:Mono10p)
        Mono12,  // Monochrome, 12 bits in 16 bits (PFNC:Mono12)
        Mono12Packed,  // Monochrome, 2x12 bits in 24 bits (GEV:Mono12Packed)
        Mono12p,  // Monochrome, 2x12 bits in 24 bits (PFNC:MonoPacked)
        Mono14,  // Monochrome, 14 bits in 16 bits (PFNC:Mono14)
        Mono16,  // Monochrome, 16 bits (PFNC:Mono16)

};




class Frame: public IData
{
public:
	Frame(    uint64_t id=0, uint64_t timestamp=0,  uint32_t width=1920,  uint32_t height = 1080, 
    PixelFormatType pixelFormat = PixelFormatType::Mono8, uint32_t size = 1920*1080);
    Frame(    uint64_t id, uint64_t timestamp,  uint32_t width,  uint32_t height, 
    PixelFormatType pixelFormat, uint32_t size, uint8_t* ptrData);
	~Frame();
    // timeout - The time to wait until the frame got filled
    bool CopyToVector(std::vector<uint8_t> &vecBuf);
    bool CopyToVector(std::vector<uint8_t> &vecBuf, uint32_t &width,  uint32_t& height);
    void Set(uint64_t id, uint64_t timestamp,  uint32_t width,  uint32_t height, 
    PixelFormatType pixelFormat, uint32_t size, uint8_t* ptrData);
    uint8_t* Pointer(){return frame.data();}
    std::vector<uint8_t>& BufRef(){return frame;}
    const std::vector<uint8_t>& BufConstRef() const {return frame;}
    uint32_t Size() const {return static_cast<uint32_t>(frame.size());}
    uint32_t Width() const {return width;}
    uint32_t Height() const {return height;}
    uint32_t PixelFormat() const {return static_cast<uint32_t>(pixelFormat);}
    uint64_t Id()  const override{return id;}   
    uint64_t Timestamp() const {return  timestamp;};//timestamp in ns
protected:

	
private:
    uint64_t id;
    uint64_t timestamp; //timestamp in ns
    uint32_t width;
    uint32_t height;
    PixelFormatType pixelFormat;
	std::vector<uint8_t> frame;

};

}

