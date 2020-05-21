
#include <mxf_exploring/ParserBCD.hpp>


uint8_t chu::parseBCDtc(uint8_t value, uint8_t tenMask)
{
    return (value & 0x0Fu) + ((value & tenMask) >> 4u) * 10u;
}
