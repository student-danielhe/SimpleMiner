#pragma once
#include "FileUtils.hpp"
#include <vector>
#include "Engine/Math/Vec2.hpp"
#include "Engine/Math/Vec3.hpp"
#include "Engine/Math/Vec4.hpp"
#include "Engine/Math/IntVec2.hpp"
#include "Engine/Math/ConvexShape.hpp"
#include "BufferWriter.hpp"
#include <vector>
class BufferParser {
    public:
		EndianMode m_endian = EndianMode::LITTLE;

		std::vector<uint8_t> m_data;
		BufferParser(void* pointer, int size);
		BufferParser(std::vector<uint8_t>* data);

		int m_readPosition = 0;

		void ParseByte(unsigned char &out_data);

		void ParseChar(char &out_data);

		void ParseUShort(unsigned short &out_data);

		void ParseShort(short &out_data);

		void ParseUInt(unsigned int &out_data);

		void ParseInt(int &out_data);

		void ParseUInt64(uint64_t &out_data);

		void ParseInt64(int64_t &out_data);

		void ParseFloat(float &out_data);

		void ParseDouble(double &out_data);

		void ParseBool(bool &out_data);

		void ParseString(std::string &out_data, bool zeroTerminated);

		void ParseVec2(Vec2 &out_data);

		void ParseVec3(Vec3 &out_data);

		void ParseVec4(Vec4 &out_data);

		void ParseIntVec2(IntVec2 &out_data);

		void ParseConvexShape(ConvexShape &out_data);

		void SetEndianMode(EndianMode newMode);

		void CopyData(void* out_data, int size);

		void ParseFile(const std::string& filePath);

		void SetReadPosition(unsigned int newPos);
};