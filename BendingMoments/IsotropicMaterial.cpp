#include "pch.h"
#include "IsotropicMaterial.h"

IsotropicMaterial StdBeamMaterials::getMaterial(const IsotropicMaterialsList material)
{
	switch (material)
	{
		case IsotropicMaterialsList::NNONE:			return IsotropicMaterial();
		case IsotropicMaterialsList::ALUMINIUM:		return aluminium;
		case IsotropicMaterialsList::STEEL:			return steel;
		case IsotropicMaterialsList::BRASS:			return brass;
		default:									return IsotropicMaterial();
	}
}