#pragma once
#include "atlstr.h"
#include <math.h>

#define __PI 3.14159265

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

enum class SectionType : int
{
	S_UNDEFINED = -1,
	S_CIRCLE,
	S_RECTANGLE,
	S_TEE,
	END_OF_SECTIONS
};

CString getSectionName(const enum class SectionType s_type);
SectionType getSectionType(const enum class SectionType s_type);
long double* getDefaultValues(const enum class SectionType s_type);

class BeamSection
{
public:
	SectionType s_type;
	size_t arraySize;
	long double* dataArray;

	CString _getSectionName();
	size_t getNumberOfArgs();
	BeamSection(
		  const enum class SectionType s_type = SectionType::S_UNDEFINED
		, const long double* _dataArray = {});
	~BeamSection();

private:
	long double getBendingIndexOfCircle();
	long double getBendingIndexOfRectangle();
	long double getBendingIndexOfTee();

public:
	long double getBendingIndex();
};

class Beam
{
public:
	BeamSection section;
	IsotropicMaterial material;

	const bool isValid();
};