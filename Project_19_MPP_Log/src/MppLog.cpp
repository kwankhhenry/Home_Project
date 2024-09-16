#include <iostream>
#include <iomanip>
#include <bitset>
#include <format>
#include <algorithm>
#include "MppLog.h"

MppLog::MppLog(const char* filename): m_file_name(filename), m_file_size(0)
{
    if(!init(filename))
    {
        std::cout << "Reading successful." << std::endl;
    }
    else
        std::cout << "Reading unsuccessful." << std::endl;
}

MppLog::~MppLog()
{
    std::for_each(p_MessagesBuff.begin(), p_MessagesBuff.end(), 
    [](MppBase* msg){ delete msg;});
}

int MppLog::init(const char* filename)
{
    m_file.open(filename, std::ios::in | std::ios::binary);
    if(!m_file)
    {
        std::cout << "Unable to read file." << std::endl;
        return -1;
    }

    // Each loop of read is expected to read a Feed Log Type, otherwise the log file is corrupted and terminate program.
    size_t msgNum = 0;
    MppBase* p_MppLog = nullptr;
    while(parseTypes(p_MppLog))
    {
        // Parse header contents and obtain each message length
        u_int32_t Message_Length = parseHeader(p_MppLog);
        parseContents(p_MppLog);

        p_MessagesBuff.push_back(p_MppLog);
        msgNum++;
    } 
    m_file.close();
    std::cout << "Number of messages read: " << std::dec << msgNum << std::endl;
    return 0;
}

bool MppLog::parseTypes(MppBase*& p_logptr)
{
    unsigned char log_type;
    // If nothing to read then return false
    if(!m_file.read(reinterpret_cast<char*>(&log_type), sizeof(log_type)))
        return false;

    // Otherwise check read byte to see if is relevant logtype
    if((log_type == 0x82) || (log_type == 0x84)|| (log_type == 0x86))
    {
        // Initialize MppBase struct obj when able to find a logtype
        p_logptr = new MppBase;

        // Record logtype
        p_logptr->m_logType = log_type;
        p_logptr->m_headerSize++;
        m_file_size += sizeof(log_type);
        return true;
    }
    else
    {
        std::cout << "Reading incorrect log type, exit program." << log_type << std::endl;
        return false;
    }
}

u_int32_t MppLog::parseHeader(MppBase* p_logptr)
{
    // Read generic information for all types
    parseField(p_logptr->m_logTime, sizeof(p_logptr->m_logTime), p_logptr);
    parseField(p_logptr->m_OMID, sizeof(p_logptr->m_OMID), p_logptr);

    // Read 0x84 and 0x86 specific details
    if(p_logptr->m_logType == 0x84 || p_logptr->m_logType == 0x86)
    {
        parseField(p_logptr->m_recv_micro, sizeof(p_logptr->m_recv_micro), p_logptr);
        parseField(p_logptr->m_reserve, sizeof(p_logptr->m_reserve), p_logptr);
    }
    
    // Read 0x86 specifics
    if(p_logptr->m_logType == 0x86)
    {
        parseField(p_logptr->m_channelID, sizeof(p_logptr->m_channelID), p_logptr);
    }
    
    // Parse Message Length
    bool is_set;
    std::bitset<sizeof(unsigned int)*8> message_length; // Assume max message length is of 4 bytes unsigned int (32 bits)
    do
    {
        // Read every byte and analyze highest bit
        u_int8_t byte;
        m_file.read(reinterpret_cast<char*>(&byte), sizeof(byte));

        // Use bitset to check to see if highest bit is 0 or not
        std::bitset<sizeof(byte)*8> b(byte);
        is_set = b.test(7);
        
        // Apply bitmask to take out the highest bit and append to message_length
        b.reset(7);
        message_length = (message_length << 7);
        message_length |= std::bitset<message_length.size()>(b.to_ulong());

        // Increment every byte read
        m_file_size++;
        p_logptr->m_headerSize++;
    } while (is_set);

    p_logptr->m_contentSize = (u_int32_t) message_length.to_ulong();
    return p_logptr->m_contentSize;
}

void MppLog::parseContents(MppBase* p_logptr)
{
    p_logptr->m_message = std::move(std::make_unique<unsigned char[]>(p_logptr->m_contentSize));
    m_file_size += p_logptr->m_contentSize;

    // Parsing raw contents into unique pointer to array ->m_message, array will be auto-deallocated upon destruction of MppLog Obj
    u_int32_t msgLength = p_logptr->m_contentSize;
    while(msgLength)
    {
        m_file.read(reinterpret_cast<char*>(&p_logptr->m_message[p_logptr->m_contentSize - msgLength]), sizeof(unsigned char));
        msgLength--;
    }
}

unsigned char MppLog::parseField(unsigned char* field, unsigned char field_size, MppBase* p_logptr)
{
    // Generic read function for all other fields
    m_file.read(reinterpret_cast<char*>(field), field_size);
    p_logptr->m_headerSize += field_size;
    this->m_file_size += field_size;
    return field_size;
}

int MppLog::getBufferSize()
{
    return p_MessagesBuff.size();
}

int MppLog::getBytesRead()
{
    return m_file_size;
}

void MppLog::getSummary()
{
    std::cout << std::setfill('-') << std::setw(50) << "\n";
    std::cout << std::format("Summary: Total number of messages: {}\n", getBufferSize());
    for(size_t i=1; i <= p_MessagesBuff.size(); i++)
    {
        std::cout << std::format("Message#[{}]: {}\n", i, getMessage(p_MessagesBuff[i-1]));
    }
    std::cout << std::format("Total size read: {} bytes.\n", getBytesRead());
    std::cout << std::setfill('-') << std::setw(50) << "\n";
}

std::string MppLog::getMessage(MppBase* p_logptr)
{
    std::stringstream oss;
    //oss << std::format("Type[{:#02x}] ", getLogType(p_logptr));
    oss << std::format("Time[{}] ", getLogTime(p_logptr));
    oss << std::format("OMID[{}] ", getOMID(p_logptr));

    if(getLogType(p_logptr) == 0x84 || getLogType(p_logptr) == 0x86)
        oss << std::format("Micro-second:[{}] ", getMicroSecond(p_logptr));

    if(getLogType(p_logptr) == 0x86)
        oss << std::format("ChannelID[{}] ", getChannelID(p_logptr));

    oss << std::format("Len[{}]\n", getMessageLen(p_logptr));
    oss << std::format("{}", getRawContent(p_logptr));
    return oss.str();
}

unsigned char MppLog::getLogType(const MppBase* const p_logptr)
{
    return p_logptr->m_logType;
}

std::string MppLog::getLogTime(const MppBase* const p_logptr)
{
    std::stringstream oss;
    oss << std::format("{0:02x}{1:02x}-{2:02x}-{3:02x} {4:02x}:{5:02x}:{6:02x}.{7:02x}{8:02x}",
        p_logptr->m_logTime[0], p_logptr->m_logTime[1], p_logptr->m_logTime[2],
        p_logptr->m_logTime[3], p_logptr->m_logTime[4], p_logptr->m_logTime[5],
        p_logptr->m_logTime[6], p_logptr->m_logTime[7], p_logptr->m_logTime[8]);
    
    return oss.str().substr(0, oss.str().length()-1);
}

std::string MppLog::getOMID(const MppBase* const p_logptr)
{
    std::stringstream oss;
    for(auto& elem: p_logptr->m_OMID)
        oss << std::format("{:02x}", elem);
    return oss.str();    
}

double MppLog::getMicroSecond(const MppBase* const p_logptr)
{
    std::stringstream oss;
    oss << std::format("{0}.{1:02}{2:02}{3:02}", 
        p_logptr->m_recv_micro[0], p_logptr->m_recv_micro[1], p_logptr->m_recv_micro[2], p_logptr->m_recv_micro[3]);
    return std::stod(oss.str())*1e6;    
}

std::string MppLog::getReserve(const MppBase* const p_logptr)
{
    std::stringstream oss;
    for(auto const& elem: p_logptr->m_reserve)
        oss << std::format("{:02x} ", elem);
    return oss.str();   
}

u_int16_t MppLog::getChannelID(const MppBase* const p_logptr)
{
    u_int16_t channel_ID = (p_logptr->m_channelID[1] << 8) | p_logptr->m_channelID[0];
    return channel_ID;
}

u_int32_t MppLog::getMessageLen(const MppBase* const p_logptr)
{
    return p_logptr->m_contentSize;   
}

std::string MppLog::getRawContent(const MppBase* const p_logptr)
{
    std::stringstream oss;
    u_int32_t bytes_read = p_logptr->m_contentSize;
    u_int32_t itemsPerRow = 16;
    u_int32_t rows = 0;
    u_int32_t rowTotal = bytes_read/itemsPerRow + (bytes_read%itemsPerRow == 0 ? 0:1);
    
    while(rows < rowTotal)
    {
        //itemsPerRow = (bytes_read > itemsPerRow ? itemsPerRow: bytes_read);
        for(size_t i=0; i<itemsPerRow; i++)
        {
            if(i < bytes_read)
                oss << std::format("{:02X} ", p_logptr->m_message[p_logptr->m_contentSize - bytes_read + i]);
            else
                oss << std::format("{:2} ", " ");
        }
        oss << " - ";
        for(size_t j=0; j<itemsPerRow; j++)
        {
            if(j < bytes_read)
                // Using std::isgraph from <ctype.h> to determine if the given unsigned char is "printable", otherwise return a dot '.'
                // Ref: https://en.cppreference.com/w/c/string/byte/isgraph
                oss << std::format("{:c} ", std::isgraph(p_logptr->m_message[p_logptr->m_contentSize - bytes_read + j]) ? 
                    p_logptr->m_message[p_logptr->m_contentSize - bytes_read + j]: '.');
            else
                oss << std::format("{:2} ", " ");                
        }
        bytes_read -= itemsPerRow;
        rows++;
        oss << std::endl;
    }
    return oss.str();
}