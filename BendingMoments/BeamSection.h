#pragma once
#include "IsotropicMaterial.h"
#include <math.h>

#define __PI 3.14159265

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

class BeamSection
{
public:
	CString sectionName;
	SectionType s_type;
	IsotropicMaterial sectionMaterial;
	size_t arraySize;
	long double* dataArray;

	CString _getSectionName();
	size_t getNumberOfArgs();
	BeamSection(
		  const enum class SectionType s_type = SectionType::S_UNDEFINED
		, const IsotropicMaterial material = IsotropicMaterial()
		, const long double dataArray[] = {});
	~BeamSection();
	const bool isValid();

private:
	long double getBendingIndexOfCircle();
	long double getBendingIndexOfRectangle();
	long double getBendingIndexOfTee();

public:
	long double getBendingIndex();
};