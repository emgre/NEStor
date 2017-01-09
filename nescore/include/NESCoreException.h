#ifndef NESCOREEXCEPTION_H
#define NESCOREEXCEPTION_H

#include <stdexcept>

namespace nescore
{
	class NESCoreException : public std::logic_error
	{
	public:
		NESCoreException(const std::string& what)
		:std::logic_error(what)
		{
		}
	};

	class NotImplementedException : public NESCoreException
	{
	public:
		NotImplementedException(const std::string& what)
		:NESCoreException(what)
		{
		}
	};

	class UndefinedOpcode : public NESCoreException
	{
	public:
		UndefinedOpcode(const std::string& what)
		:NESCoreException(what)
		{
		}
	};

	class InvalidROMFile : public NESCoreException
	{
		public:
		InvalidROMFile(const std::string& what)
		:NESCoreException(what)
		{
		}
	};
}

#endif // NESCOREEXCEPTION_H