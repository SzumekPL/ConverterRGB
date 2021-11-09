#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

struct Color888
{
    Color888() = default;
    Color888(unsigned char r, unsigned char g, unsigned char b) : red(r), green(g), blue(b) {}

    unsigned char red = 0;
    unsigned char green = 0;
    unsigned char blue = 0;

    friend bool operator == (const Color888& l_val, const Color888& r_val)
    {
        return (l_val.red == r_val.red)
                && (l_val.green == r_val.green)
                && (l_val.blue == r_val.blue);
    }

    friend bool operator != (const Color888& l_val, const Color888& r_val)
    {
        return !(l_val == r_val);
    }
};

struct Color555
{
    Color555() = default;
    Color555(unsigned char byte1, unsigned char byte2) : byte1(byte1), byte2(byte2) {}

    unsigned char byte1 = 0;
    unsigned char byte2 = 0;

    friend bool operator == (const Color555& l_val, const Color555& r_val)
    {
        return (l_val.byte1 == r_val.byte1) && (l_val.byte2 == r_val.byte2);
    }

    friend bool operator != (const Color555& l_val, const Color555& r_val)
    {
        return !(l_val == r_val);
    }
};

Color555 convert888to555(const Color888& color)
{
    unsigned char red5 = color.red >> 3;
    red5 &= 0b00011111;
    unsigned char green5 = color.green >> 3;
    green5 &= 0b00011111;
    unsigned char blue5 = color.blue >> 3;
    blue5 &= 0b00011111;

    Color555 result;
    result.byte1 |= red5;
    result.byte1 |= (green5 << 5);

    result.byte2 |= (green5 >> 3);
    result.byte2 |= (blue5 << 2);

    return result;
}

Color888 convert555to888(const Color555& color)
{
   unsigned char red5 = color.byte1 & 0b00011111;
   unsigned char blue5 = (color.byte2 & 0b01111100) >> 2;
   unsigned char green5 = ((color.byte2 & 0b00000011) << 3) | ((color.byte1 & 0b11100000) >> 5);

   Color888 result;
   result.red = (red5 << 3);
   result.green = (green5 << 3);
   result.blue = (blue5 << 3);

   return result;
}

int main()
{
   Color888 a(255,255,255);
   Color888 b(123,123,123);
   Color888 c(123,123,123);

   std::cout << "Test operatora Color888 True: "  << (b == c) << std::endl;
   std::cout << "Test operatora Color888 False: " << (a != c) << std::endl;
   std::cout << "Test operatora Color888 False: " << (b != a) << std::endl;

   //--------------------------------------------------------------------

   Color555 x(255,255);
   Color555 y(123,123);
   Color555 z(123,123);

   std::cout << "Test operatora Color555 True: "  << (y == z) << std::endl;
   std::cout << "Test operatora Color555 False: " << (x != z) << std::endl;
   std::cout << "Test operatora Color555 False: " << (y != x) << std::endl;

   //------------------------------------------------------------------

   int colors_max = 1 << 15;
   bool result = true;

   for(int i = 0; i < colors_max; ++i)
   {
       unsigned char byte1 = (i & 0b11111111);
       unsigned char byte2 = (i >> 8);
       Color555 test(byte1, byte2);

       if(convert888to555(convert555to888(test)) != test)
       {
           result = false;
           break;
       }
   }

   if(result)
   {
       std::cout << "SUCCESS! \n";
   }
   else
   {
       std::cout << "FAILED! \n";
   }
}
