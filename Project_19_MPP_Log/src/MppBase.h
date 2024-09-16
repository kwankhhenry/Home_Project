#pragma once

#include <iostream>
#include <memory>

struct MppBase
{
    unsigned char m_logType;
    unsigned char m_logTime[9];
    unsigned char m_OMID[8];
    unsigned char m_recv_micro[4];
    unsigned char m_reserve[8];
    unsigned char m_channelID[2];
    std::unique_ptr<unsigned char[]> m_message;

    // Statistics
    u_int32_t m_headerSize = 0;
    u_int32_t m_contentSize = 0;
};