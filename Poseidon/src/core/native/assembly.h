#pragma once
#ifndef _ASSEMBLY_
#define _ASSEMBLY_
namespace poseidon::core::native
{
	class assembly
	{
	public:
		assembly(int assemblyId);

		~assembly()
		{
		}

	private:
		int m_assemblyId;
	};

}
#endif // !_ASSEMBLY_
