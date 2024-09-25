#include "host.h"
#include "CoreCLR.h"

namespace poseidon::core
{
	host::~host()
	{
		HostFxr::close(m_handle);
		m_handle = nullptr;
	}
}
