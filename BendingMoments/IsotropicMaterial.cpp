#include "pch.h"
#include "IsotropicMaterial.h"

IsotropicMaterial::IsotropicMaterial(
	const enum class IsotropicMaterials material_type
	, const long double& youngModulus
	, const long double& poissonsNumber) {
	this->material_type = material_type;
	this->youngModulus = youngModulus;
	this->poissonsNumber = poissonsNumber;
}

IsotropicMaterial getMaterial(const IsotropicMaterials material) {
	switch (material)
	{
		case IsotropicMaterials::ALUMINIUM:		return aluminium;
		case IsotropicMaterials::STEEL:			return steel;
		case IsotropicMaterials::BRASS:			return brass;
		default:								return IsotropicMaterial();
	}
}

CString getMaterialName(const enum class IsotropicMaterials material) {
	switch (material)
	{
		case IsotropicMaterials::ALUMINIUM:		return _T("Aluminium");
		case IsotropicMaterials::STEEL:			return _T("Steel");
		case IsotropicMaterials::BRASS:			return _T("Brass");
		default:								return _T("Undefined");
	}
}