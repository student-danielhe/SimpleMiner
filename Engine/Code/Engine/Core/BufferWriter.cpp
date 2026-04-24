#include "Engine/Core/BufferWriter.hpp"

BufferWriter::BufferWriter(std::vector<uint8_t>* data)
{
    m_data = data;
    m_endian = GetNativeEndianMode();
}

void BufferWriter::AppendByte(unsigned char data)
{
    m_data->push_back(data);
}

void BufferWriter::AppendChar(char data)
{
    m_data->push_back(data);
}

void BufferWriter::AppendUShort(unsigned short data)
{
    std::vector<unsigned char> asArray = TurnIntoByteArray(&data, sizeof(unsigned short));

    AppendDataArrayBasedOnEndian(asArray);

}

void BufferWriter::AppendShort(short data)
{
	std::vector<unsigned char> asArray = TurnIntoByteArray(&data, sizeof(short));

	AppendDataArrayBasedOnEndian(asArray);
}

void BufferWriter::AppendUInt(unsigned int data)
{
	std::vector<unsigned char> asArray = TurnIntoByteArray(&data, sizeof(unsigned int));

	AppendDataArrayBasedOnEndian(asArray);
}

void BufferWriter::AppendInt(int data)
{
	std::vector<unsigned char> asArray = TurnIntoByteArray(&data, sizeof(int));

	AppendDataArrayBasedOnEndian(asArray);
}

void BufferWriter::AppendUInt64(uint64_t data)
{
	std::vector<unsigned char> asArray = TurnIntoByteArray(&data, sizeof(uint64_t));

	AppendDataArrayBasedOnEndian(asArray);
}

void BufferWriter::AppendInt64(int64_t data)
{
	std::vector<unsigned char> asArray = TurnIntoByteArray(&data, sizeof(int64_t));

	AppendDataArrayBasedOnEndian(asArray);
}

void BufferWriter::AppendFloat(float data)
{
	std::vector<unsigned char> asArray = TurnIntoByteArray(&data, sizeof(float));

	AppendDataArrayBasedOnEndian(asArray);
}

void BufferWriter::AppendDouble(double data)
{
	std::vector<unsigned char> asArray = TurnIntoByteArray(&data, sizeof(double));

	AppendDataArrayBasedOnEndian(asArray);
}

void BufferWriter::AppendBool(bool data)
{
	AppendByte(data);
}

void BufferWriter::AppendString(std::string data, bool zeroTerminated)
{
	if (!zeroTerminated) {
        AppendUInt((unsigned int)data.size());
	}

    for (int i = 0; i < data.size(); i++) {
        AppendChar(data[i]);
    }

	if (zeroTerminated) {
        AppendChar('0');
	}
}

void BufferWriter::AppendVec2(Vec2 data)
{
	AppendFloat(data.x);
    AppendFloat(data.y);
}

void BufferWriter::AppendVec3(Vec3 data)
{
	AppendFloat(data.x);
	AppendFloat(data.y);
	AppendFloat(data.z);
	
}

void BufferWriter::AppendVec4(Vec4 data)
{
	AppendFloat(data.x);
	AppendFloat(data.y);
	AppendFloat(data.z);
	AppendFloat(data.w);
}

void BufferWriter::AppendIntVec2(IntVec2 data)
{
	AppendInt(data.x);
	AppendInt(data.y);
}

void BufferWriter::AppendConvexShape(ConvexShape data)
{

}

void BufferWriter::SetEndianMode(EndianMode newMode)
{
    m_endian = newMode;
}

void BufferWriter::RandomAccessOverwrite(unsigned int pos, unsigned int data)
{
/*
   std::vector<unsigned char> asArray = TurnIntoByteArray(&data, sizeof(unsigned int));

   unsigned int writePos = pos;

   char* temp;

   std::memcpy(temp, &data, sizeof(unsigned int));

   if (m_endian == BufferWriter::GetNativeEndianMode()) {

	   for (int i = 0; i < sizeof(unsigned int); i++) {
		   m_data[writePos + i] = temp[i];
	   }

   }
   else {
	   for (int i = 0; i < sizeof(unsigned int); i++) {
		   m_data[writePos + i] = temp[sizeof(unsigned int) - i - 1];
	   }
   }*/

}

std::vector<unsigned char> BufferWriter::TurnIntoByteArray(void* data, int size)
{
    std::vector<unsigned char> result;
    result.resize(size);

    std::memcpy(result.data(), data, size);

    return result;
}

void BufferWriter::AppendDataArrayBasedOnEndian(std::vector<unsigned char> data)
{
    if (m_endian == BufferWriter::GetNativeEndianMode()) {
        
        for (int i = 0; i < data.size(); i++) {
            AppendByte(data[i]);
        }

    }
    else {
        for (int i = 0; i < data.size(); i++) {
            AppendByte(data[data.size()-i-1]);
        }
    }
}

EndianMode BufferWriter::GetNativeEndianMode()
{
    unsigned int data = 0x12345678;

    std::vector<unsigned char> asArray = BufferWriter::TurnIntoByteArray(&data, sizeof(unsigned int));

    if (asArray[0] == 0x12) {
        return EndianMode::BIG;
    }

    if (asArray[0] == 0x78) {
        return EndianMode::LITTLE;
    }

    return EndianMode::COUNT;
}

void BufferWriter::WriteFile(const std::string& filePath)
{
    FileWriteBuffer( m_data, filePath);
}

