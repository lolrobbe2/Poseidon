#include "garbageCollector.h"
#include <core/delegates/garbageCollectorDelegates.h>
#include <core/host.h>
namespace poseidon::core
{
	struct garbageCollectorFunctions
	{
		f_collectGarbage collectGarbagePtr = nullptr;
		f_unpinHandle GCHandleFreePtr = nullptr;
	};
	garbageCollector::garbageCollector(r_host host) : p_host(host)
	{
		if (p_garbageCollectorFunctions) return;
		p_garbageCollectorFunctions = new garbageCollectorFunctions();
		p_host->getUnmangedFunctionPtr(PD_STR("PoseidonSharp.managed.GarbageCollector, PoseidonSharp"), PD_STR("Collect"), (void**)&p_garbageCollectorFunctions->collectGarbagePtr);
		p_host->getUnmangedFunctionPtr(PD_STR("PoseidonSharp.managed.GarbageCollector, PoseidonSharp"), PD_STR("GCHandleFree"), (void**)&p_garbageCollectorFunctions->GCHandleFreePtr);

	}

	void garbageCollector::collect() const
	{
		if (!p_host->isValid()) return;
		p_garbageCollectorFunctions->collectGarbagePtr();
	}
	void garbageCollector::unpinHandle(void* handle) const
	{
		if (!p_host->isValid()) return;
		p_garbageCollectorFunctions->GCHandleFreePtr(handle);
	}
}