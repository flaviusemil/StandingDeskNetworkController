#ifndef CORE_BIN_FS_H
#define CORE_BIN_FS_H

#include <stdint.h>

//#pragma pack(push, 1)
struct Version {
    uint8_t major_version;
    uint8_t minor_version;
};

struct Header {
    int64_t magic_bytes;
    Version version;
    int16_t offset_to_data;
    int32_t checksum;
};

struct Body {
    int32_t attr_type;
    int32_t attr_len_inc_header;
    uint8_t name_len;
    uint16_t name_offset;
    uint16_t flags;
    uint16_t attr_id;
    int32_t attr_body_len;
    int16_t attr_offset;
    uint8_t indexed_flg;
    int16_t dummy;
};

struct BinaryFile {
    Header header;
    Body body;
    int32_t checksum;
};
//#pragma pack(pop)
#endif
