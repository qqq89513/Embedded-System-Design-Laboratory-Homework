#include <gui/common/BMPFileLoader.hpp>
#include <touchgfx/Color.hpp>

#define FILE_BUF_SIZE 55
#define P 16     // how many pixels to read from file at a time, p*3 should be smaller than sizeof(data)
#if (P*3+3 > FILE_BUF_SIZE)
#error "Insufficient size of image buffer data. Try to lower p or increase size of data."
#endif

int BMPFileLoader::readFile(FileHdl hdl, uint8_t* const buffer, uint32_t length)
{
  #ifdef SIMULATOR
    uint32_t r;
    r = fread(buffer, 1, length, (FILE*)hdl);
  #else
    unsigned int r;
    f_read(hdl, buffer, length, &r);
  #endif

  if (r != length)
    return 1;
  return 0;
}

void BMPFileLoader::seekFile(FileHdl hdl, uint32_t offset)
{
  #ifdef SIMULATOR
    fseek((FILE*)hdl, offset, SEEK_SET);
  #else
    f_lseek(hdl, (FSIZE_t)offset);
  #endif
}

void BMPFileLoader::getBMP24Dimensions(FileHdl fileHandle, uint16_t& width, uint16_t& height)
{
  uint8_t data[50];
  seekFile(fileHandle, 0);
  readFile(fileHandle, data, 26); //read first part of header.

  width = data[18] | (data[19] << 8) | (data[20] << 16) | (data[21] << 24);
  height = data[22] | (data[23] << 8) | (data[24] << 16) | (data[25] << 24);
}

void BMPFileLoader::readBMP24File(Bitmap bitmap, FileHdl fileHandle)
{
  uint8_t data[FILE_BUF_SIZE];

 // Read header
  seekFile(fileHandle, 0);
  readFile(fileHandle, data, 26);
  const uint32_t offset = data[10] | (data[11] << 8) | (data[12] << 16) | (data[12] << 24);
  const uint32_t f_width = data[18] | (data[19] << 8) | (data[20] << 16) | (data[21] << 24);  // width read  from the bmp file
  const uint32_t f_height = data[22] | (data[23] << 8) | (data[24] << 16) | (data[25] << 24); // height read from the bmp file
  readFile(fileHandle, data, offset - 26);  // Skip the rest of header

  // Get dynamic bitmap boundaries
  const uint32_t buffer_width  = bitmap.getWidth();       // width  of the bitmap
  const uint32_t buffer_height = bitmap.getHeight();      // height of the bitmap
  const uint32_t rowpadding = (4 - ((f_width*3)%4)) % 4;  // how many unused bytes at the end of a row

  const Bitmap::BitmapFormat format = bitmap.getFormat();
  uint8_t* const  buffer8  = Bitmap::dynamicBitmapGetAddress(bitmap.getId()); // Address of the bitmap cache
  uint16_t* const buffer16 = (uint16_t*)buffer8;                              // Address of the bitmap cache
  
  // Read pixels from file and insert to bitmap cache
  for (uint32_t y = 0; y < f_height; y++){
    for (uint32_t x = 0; x < f_width; x++){
      
      // Read data every 10 pixels
      if (x % P == 0){
        if (x + P <= f_width) // Non edge condition
          readFile(fileHandle, data, P*3); // 1 pixels = 3 bytes
        else                  // Rest of line
          readFile(fileHandle, data, (f_width-x)*3 + rowpadding);   // (+rowpadding) to skip the rest of data in the row
      }

      // Insert a pixel if (x,y) within dynamic bitmap boundaries
      if (x < buffer_width && ((f_height-y-1) < buffer_height)){
        switch (format){
          case Bitmap::RGB565:
            buffer16[x + (f_height-y-1)*buffer_width] = touchgfx::Color::getColorFrom24BitRGB(
              data[ (x%P)*3 + 2 ],   // Read
              data[ (x%P)*3 + 1 ],   // Green
              data[ (x%P)*3 + 0 ]);  // Blue
                //[ (ith pixel)*3 + offset]
            break;

          case Bitmap::RGB888:{
            //24 bit framebuffer
            const uint32_t inx = 3 * (x + (f_height-y-1)*buffer_width);
            buffer8[inx + 0] = data[ (x%10)*3 + 0] ;
            buffer8[inx + 1] = data[ (x%10)*3 + 1] ;
            buffer8[inx + 2] = data[ (x%10)*3 + 2] ;
            break;
          }
          case Bitmap::ARGB8888:{
            //24 bit framebuffer
            const uint32_t inx = 4 * (x + (f_height-y-1)*buffer_width);
            buffer8[inx + 0] = data[ (x%10)*3 + 0 ];
            buffer8[inx + 1] = data[ (x%10)*3 + 1 ];
            buffer8[inx + 2] = data[ (x%10)*3 + 2 ];
            buffer8[inx + 3] = 255; //solid
            break;
          }
          default:
            assert(!"Unsupported bitmap format in BMPFileLoader!");
        }
      }
    }
  }
}
