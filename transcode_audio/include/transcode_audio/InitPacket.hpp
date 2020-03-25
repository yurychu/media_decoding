#pragma once

#include <common/macro_c_extern.hpp>

EXTERN_C_BEGIN
#include <libavcodec/avcodec.h>
EXTERN_C_END


namespace tr_au
{

    /**
     * Initialize one data packet for reading or writing.
     * @param packet Packet to be initialized
     */
    void init_packet(AVPacket *packet);


}
