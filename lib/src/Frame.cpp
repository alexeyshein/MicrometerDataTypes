#include <iostream>
#include "Frame.h"


using namespace::rf;


Frame::	Frame( uint64_t id_, uint64_t timestamp_,  uint32_t width_,  uint32_t height_, 
    PixelFormatType pixelFormat_,  uint32_t offsetX, uint32_t offsetY, uint32_t size):
    IData()
    , id(id_)
    , timestamp(timestamp_)
    , width(width_)
    , height(height_)
    , pixelFormat(pixelFormat_)
    , frame(size,0)
    , offsetX (offsetX)
    , offsetY (offsetY)
{}

Frame::Frame(    uint64_t id_, uint64_t timestamp_,  uint32_t width_,  uint32_t height_, 
        PixelFormatType pixelFormat_, uint32_t offsetX_, uint32_t offsetY_,  uint32_t size, uint8_t* ptrData):
      Frame(id_, timestamp_,  width_,  height_, pixelFormat_, offsetX_, offsetY_, size)
{
      std::copy(ptrData, ptrData+size,  frame.begin());
}

Frame::~Frame()
{
 //	Close();	
}

void Frame::Set(uint64_t id_, uint64_t timestamp_,  uint32_t width_,  uint32_t height_, 
        PixelFormatType pixelFormat_, uint32_t size, uint8_t* ptrData)
{
   id=id_;
   timestamp = timestamp_;
   width=width_;
   height=height_;
   pixelFormat=pixelFormat_;
   frame.resize(size);
   std::copy(ptrData, ptrData+size,  frame.begin()); //100~2500 mks
   offsetX = 0;
   offsetY = 0;
}

void Frame::Set(uint64_t id_, uint64_t timestamp_,  uint32_t width_,  uint32_t height_,
         PixelFormatType pixelFormat_, uint32_t size, uint32_t offsetX_,  uint32_t offsetY_,  uint8_t* ptrData)
{
   id=id_;
   timestamp = timestamp_;
   width=width_;
   height=height_;
   pixelFormat=pixelFormat_;
   offsetX=offsetX_;
   offsetY=offsetY_;
   frame.resize(size);
   std::copy(ptrData, ptrData+size,  frame.begin()); //100~2500 mks
}
bool Frame::CopyToVector(std::vector<uint8_t> &vecBuf)
{
	vecBuf.resize(Size());
    std::copy(frame.data(), frame.data()+Size(),
                  vecBuf.begin());
	return true;
}

bool Frame::CopyToVector(std::vector<uint8_t> &vecBuf, uint32_t &widthOut,  uint32_t& heightOut)
{
  if(CopyToVector(vecBuf)){
	  widthOut = width;
	  heightOut = height;
	  return true;
  }
  else{
	  return false;
  }
}
