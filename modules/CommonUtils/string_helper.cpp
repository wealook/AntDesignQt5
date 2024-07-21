#include "string_helper.h"
#if defined(HAVE_CODECVT)
#include <codecvt>
#endif
#include <string>
#if defined(_WIN32)
#include "Windows.h"
#endif
#if defined(LINUX_GCC)
	#include <locale>
#endif
using namespace wl;

    std::string StringHelper::ws2s(const std::wstring& src)
    {
#if defined(HAVE_CODECVT)
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.to_bytes(src);
#else
	return std::string();
#endif
    }

	// utf8 to unicode
	std::wstring StringHelper::s2ws(const std::string & str)
	{
		std::wstring ret;
#if defined(HAVE_CODECVT)
		try {
			std::wstring_convert<std::codecvt_utf8<wchar_t>> wcv;
			ret = wcv.from_bytes(str);
		}
		catch (...) {
		}
#endif
		return ret;
	}

	//GBK 2 unicode
	std::wstring StringHelper::ls2ws(const std::string& input)
	{
		std::wstring result;

#if defined(_WIN32)
		int requiredUnicode = MultiByteToWideChar(CP_ACP, 0, input.data(), (int)input.length(), NULL, 0);
		wchar_t *unicodedStr = new wchar_t[requiredUnicode];
		wmemset(unicodedStr, 0, requiredUnicode);

		int parsedUnicode = MultiByteToWideChar(CP_ACP, 0, input.data(), (int)input.length(), unicodedStr, requiredUnicode);

		if (parsedUnicode == requiredUnicode) {
			result = std::wstring(unicodedStr, parsedUnicode);
		}
		delete[] unicodedStr;
#endif
		return result;
	}

	//unicode to GBK
	std::string StringHelper::ws2ls(const std::wstring& unicodeStr)
	{
		std::string result;

#if defined(_WIN32)
		int requiredAnsi = WideCharToMultiByte(CP_ACP, 0, unicodeStr.data(), (int)unicodeStr.length(), nullptr, 0, nullptr, nullptr);
		char *ansiStr = new char[requiredAnsi];
		memset(ansiStr, 0, requiredAnsi);

		int parsedAnsi = WideCharToMultiByte(CP_ACP, 0, unicodeStr.data(), (int)unicodeStr.length(), ansiStr, requiredAnsi, nullptr, nullptr);
		if (parsedAnsi == requiredAnsi) {
			result = std::string(ansiStr, requiredAnsi);
		}
		delete[] ansiStr;
#endif
		return result;
	}

