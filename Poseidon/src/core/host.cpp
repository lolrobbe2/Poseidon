#include "host.h"
#include "CoreCLR.h"

namespace poseidon::core
{
	host::~host()
	{
		release();
	}
	void host::release()
	{
		if (!isValid()) return;
		HostFxr::close(m_handle);
		m_handle = nullptr;
	}
}
