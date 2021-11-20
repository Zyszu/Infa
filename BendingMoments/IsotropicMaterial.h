#pragma once
#include "atlstr.h"

class IsotropicMaterial
{
public:
	CString name;
	long double youngModulus;
	long double poissonsNumber;

	IsotropicMaterial(
		  const CString& name = (CString)("undefind")
		, const long double& youngModulus = 2 * 100000
		, const long double& poissonNumber = 0.3)
	{
		this->name = name;
		this->youngModulus = youngModulus;
		this->poissonsNumber = poissonsNumber;
	}
};

namespace StdBeamMaterials
{
	const IsotropicMaterial steel((CString)"Steel", 2.1 * 100000);
	const IsotropicMaterial aluminium((CString)"Aluminium", 6.9 * 10000, 0.33);
	const IsotropicMaterial brass((CString)"Brass", 1.2 * 100000, 0.4);	

	enum class IsotropicMaterialsList : int {
		NNONE = -1,
		ALUMINIUM,
		BRASS,
		STEEL
	};

	IsotropicMaterial getMaterial(const IsotropicMaterialsList material);
}