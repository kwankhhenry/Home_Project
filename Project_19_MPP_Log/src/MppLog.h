#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "MppBase.h"

class MppLog
{
private:
    std::vector<MppBase*> p_MessagesBuff;
    const char* m_file_name;
    u_int32_t m_file_size;
    std::ifstream m_file;
protected:
    bool parseTypes(MppBase*& p_logptr);
    u_int32_t parseHeader(MppBase* p_logptr);
    void parseContents(MppBase* p_logptr);
    unsigned char parseField(unsigned char* field, unsigned char field_size, MppBase* p_logptr);
public:
    MppLog(const char* filename);
    ~MppLog();

    // Initialize parsing
    int init(const char* filename);

    // Entire buffer accessors
    int getBufferSize();
    int getBytesRead();
    void getSummary();

    // Individual element accessors (return in strings)
    std::string getMessage(MppBase* p_logptr);
    unsigned char getLogType(const MppBase* const p_logptr);
    std::string getLogTime(const MppBase* const p_logptr);
    std::string getOMID(const MppBase* const p_logptr);
    double getMicroSecond(const MppBase* const p_logptr);
    std::string getReserve(const MppBase* const p_logptr);
    u_int16_t getChannelID(const MppBase* const p_logptr);
    u_int32_t getMessageLen(const MppBase* const p_logptr);
    std::string getRawContent(const MppBase* const p_logptr);
};