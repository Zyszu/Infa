#pragma once
#include "atlstr.h"

enum class IsotropicMaterials : int {
	NONE = -1,
	ALUMINIUM,
	BRASS,
	STEEL,
	END_OF_MATERIALS
};

class IsotropicMaterial
{
public:
	IsotropicMaterials material_type;
	long double youngModulus;
	long double poissonsNumber;

	IsotropicMaterial(
		const enum class IsotropicMaterials material_type = IsotropicMaterials::NONE
		, const long double& youngModulus = 0
		, const long double& poissonsNumber = 0);
};

const IsotropicMaterial steel(IsotropicMaterials::STEEL, 2.1 * 100000, 0.3);
const IsotropicMaterial aluminium(IsotropicMaterials::ALUMINIUM, 6.9 * 10000, 0.33);
const IsotropicMaterial brass(IsotropicMaterials::BRASS, 1.2 * 100000, 0.4);

IsotropicMaterial getMaterial(const IsotropicMaterials material);
CString getMaterialName(const enum class IsotropicMaterials material);