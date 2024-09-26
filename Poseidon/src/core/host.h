#pragma once
#ifndef _HOST_
#define _HOST_
typedef void* hostHandle;
namespace poseidon::core
{
	class host
	{
	public:
		host() = default;
		host(hostHandle handle) : m_handle(handle)
		{
		}

		~host();
		const hostHandle native() const { return m_handle; }
		void release();
		bool isValid() const { return m_handle; }
		operator bool() const { return m_handle; }
	private:
		hostHandle m_handle;
	};

}
#endif // !_HOST_



