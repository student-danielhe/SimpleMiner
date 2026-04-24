#include "BufferParser.hpp"
#include "Engine/Core/ErrorWarningAssert.hpp"

BufferParser::BufferParser(std::vector<uint8_t>* data)
{
    m_data = *data;
}

BufferParser::BufferParser(void* pointer, int size)
{
    std::memcpy(m_data.data(), pointer, size);
}

void BufferParser::ParseByte(unsigned char& out_data)
{
    unsigned char data = '0';
    CopyData(&data, sizeof(unsigned char));
    out_data = data;

    m_readPosition += sizeof(unsigned char);
}

void BufferParser::ParseChar(char& out_data)
{
	char data = '0';
    int size = sizeof(char);

	CopyData(&data, size);
	out_data = data;

	m_readPosition += size;
}

void BufferParser::ParseUShort(unsigned short& out_data)
{
	unsigned short data = 0;
	int size = sizeof(unsigned short);

	CopyData(&data, size);
	out_data = data;

	m_readPosition += size;
}

void BufferParser::ParseShort(short& out_data)
{
	short data = 0;
	int size = sizeof(short);

	CopyData(&data, size);
	out_data = data;

	m_readPosition += size;
}

void BufferParser::ParseUInt(unsigned int& out_data)
{
	unsigned int data = 0;
	int size = sizeof(unsigned int);

	CopyData(&data, size);
	out_data = data;

	m_readPosition += size;
}

void BufferParser::ParseInt(int& out_data)
{
	int data = 0;
	int size = sizeof(int);

	CopyData(&data, size);
	out_data = data;

	m_readPosition += size;
}

void BufferParser::ParseUInt64(uint64_t& out_data)
{
	uint64_t data = 0;
	int size = sizeof(uint64_t);

	CopyData(&data, size);
	out_data = data;

	m_readPosition += size;
}

void BufferParser::ParseInt64(int64_t& out_data)
{
	int64_t data = 0;
	int size = sizeof(int64_t);

	CopyData(&data, size);
	out_data = data;

	m_readPosition += size;
}

void BufferParser::ParseFloat(float& out_data)
{
	float data = 0.f;
	int size = sizeof(float);

	CopyData(&data, size);
	out_data = data;

	m_readPosition += size;
}

void BufferParser::ParseDouble(double& out_data)
{
	double data = 0;
	int size = sizeof(double);

	CopyData(&data, size);
	out_data = data;

	m_readPosition += size;
}

void BufferParser::ParseBool(bool& out_data)
{
	bool data = false;
	int size = sizeof(bool);

	CopyData(&data, size);
	out_data = data;

	m_readPosition += size;
}

void BufferParser::ParseString(std::string& out_data, bool zeroTerminated)
{
    out_data = "";
    unsigned int size = 0;
	if (!zeroTerminated) {
	    ParseUInt(size);

		for (int i = 0; i < size; i++) {
			char c;
			ParseChar(c);
			out_data+=c;
		}
	}

	if (zeroTerminated) {
	    char c;
		ParseChar(c);

		while (c!= '0')
		{
			out_data+=c;
			ParseChar(c);
			
		}
	}
	
}

void BufferParser::ParseVec2(Vec2& out_data)
{
	ParseFloat(out_data.x);
	ParseFloat(out_data.y);
}

void BufferParser::ParseVec3(Vec3& out_data)
{
     ParseFloat(out_data.x);
	 ParseFloat(out_data.y);
	 ParseFloat(out_data.z);
}

void BufferParser::ParseVec4(Vec4& out_data)
{
	ParseFloat(out_data.x);
	ParseFloat(out_data.y);
	ParseFloat(out_data.z);
	ParseFloat(out_data.w);
}

void BufferParser::ParseIntVec2(IntVec2& out_data)
{
	ParseInt(out_data.x);
	ParseInt(out_data.y);
}

void BufferParser::ParseConvexShape(ConvexShape& out_data)
{

}

void BufferParser::SetEndianMode(EndianMode newMode)
{
    m_endian = newMode;
}

void BufferParser::CopyData(void* out_data, int size)
{
	if (m_readPosition >= m_data.size()||m_readPosition<0) {
		ERROR_AND_DIE("Invalid Read Position");
	}
	if (m_endian != BufferWriter::GetNativeEndianMode()) {
		std::vector<uint8_t> arr;
		arr.resize(size);
		for (int i = 0; i< size; i++) {
		    arr[i] = m_data[m_readPosition + size - i - 1];
		}

		 std::memcpy(out_data, arr.data(), size);
	}
	else {
	    std::memcpy(out_data, m_data.data() + m_readPosition, size);
	}
    
}

void BufferParser::ParseFile(const std::string& filePath)
{
    FileReadToBuffer(m_data, filePath);
}

void BufferParser::SetReadPosition(unsigned int newPos)
{
    m_readPosition = newPos;
}

