#include <stdio.h>
#include <vector>
#include "../includes/CoreBinFS.h"
#include <zlib.h>

const uint8_t MAGIC_BYTES[] = { 0xB0, 0x6F, 0x74, 0x62, 0x0D, 0x0A, 0x1A, 0x0A };

uint32_t calculateCRC32(const void* data, size_t size) {
    uint32_t crc = crc32(0L, Z_NULL, 0);
    crc = crc32(crc, reinterpret_cast<const Bytef*>(data), size);
    return crc;
}

void writeBinaryFile(const char* filename, const BinaryFile& binary_file) {
    FILE* file = fopen(filename, "wb"); // Open the file in binary write mode

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Write the BinaryFile struct to the file
    size_t binary_file_written = fwrite(&binary_file, sizeof(BinaryFile), 1, file);

    if (binary_file_written != 1) {
        perror("Error writing to file");
    }

    fclose(file);
}

int main(int argc, const char** argv) {
    BinaryFile file;

    // Set the Header fields
    file.header.magic_bytes = *reinterpret_cast<const int64_t*>(MAGIC_BYTES);
    file.header.version.major_version = 1;
    file.header.version.minor_version = 0;
    file.header.offset_to_data = sizeof(Header); // set the offset to the size of the Header struct
    file.header.checksum = calculateCRC32(reinterpret_cast<const void*>(&file.header), sizeof(Header) - sizeof(uint32_t));

    file.body.attr_type = 286331153;
    file.body.attr_len_inc_header = sizeof(Body);
    file.body.name_len = 1;
    file.body.name_offset = 4369;
    file.body.flags = 4369;
    file.body.attr_id = 4369;
    file.body.attr_body_len = 286331153;
    file.body.attr_offset = 4369;
    file.body.indexed_flg = 1;
    file.body.dummy = 42;
    file.checksum = calculateCRC32(reinterpret_cast<const void*>(&file), sizeof(BinaryFile) - sizeof(uint32_t));

    // Write the BinaryFile struct to the file
    const char* filename = "data.bin";
    writeBinaryFile(filename, file);

    // Print the Header fields
    printf("Magic Bytes: %llx\n", file.header.magic_bytes);
    printf("Version: %d.%d\n", file.header.version.major_version, file.header.version.minor_version);
    printf("Offset to Data: %d\n", file.header.offset_to_data);
    printf("Header checksum: 0x%08x\n", file.header.checksum);
    printf("File checksum: 0x%08x\n", file.checksum);

    printf("File size: %d\n", sizeof(BinaryFile));
    printf("Header size: %d\n", sizeof(Header));
    printf("Body size: %d\n", sizeof(Body));
    return 0;
}
