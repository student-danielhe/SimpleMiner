#pragma once
#include "FileUtils.hpp"
#include <vector>
#include "Engine/Math/Vec2.hpp"
#include "Engine/Math/Vec3.hpp"
#include "Engine/Math/Vec4.hpp"
#include "Engine/Math/IntVec2.hpp"
#include "Engine/Math/ConvexShape.hpp"

enum class EndianMode {
    BIG,
    LITTLE,
    COUNT
};


class BufferWriter {
    public:

    EndianMode m_endian;

    std::vector<uint8_t>* m_data;
    
    BufferWriter(std::vector<uint8_t>* data);

    void AppendByte(unsigned char data);

    void AppendChar(char data);

    void AppendUShort(unsigned short data);

    void AppendShort(short data);

    void AppendUInt(unsigned int data);

    void AppendInt(int data);

    void AppendUInt64(uint64_t data);

    void AppendInt64(int64_t data);

    void AppendFloat(float data);

    void AppendDouble(double data);

    void AppendBool(bool data);

    void AppendString(std::string data, bool zeroTerminated);

    void AppendVec2(Vec2 data);

    void AppendVec3(Vec3 data);

    void AppendVec4(Vec4 data);

    void AppendIntVec2(IntVec2 data);

    void AppendConvexShape(ConvexShape data);

    void SetEndianMode(EndianMode newMode);

    void RandomAccessOverwrite(unsigned int pos, unsigned int data);

    static::std::vector<unsigned char> TurnIntoByteArray(void* data, int size);

    void AppendDataArrayBasedOnEndian(std::vector<unsigned char> data);

    static::EndianMode GetNativeEndianMode();

    void WriteFile(const std::string& filePath);
};