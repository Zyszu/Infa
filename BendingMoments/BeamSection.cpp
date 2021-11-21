#include "pch.h"
#include "BeamSection.h"

CString getSectionName(const enum class SectionType s_type) {
	switch (s_type)
	{
		case SectionType::S_CIRCLE:		return _T("Circle");
		case SectionType::S_RECTANGLE:	return _T("Rectangle");
		case SectionType::S_TEE:		return _T("Tee");
		default:						return _T("Undefined");
	}
}

SectionType getSectionType(const enum class SectionType s_type)
{
	switch (s_type)
	{
		case SectionType::S_CIRCLE:		return SectionType::S_CIRCLE;
		case SectionType::S_RECTANGLE:	return SectionType::S_RECTANGLE;
		case SectionType::S_TEE:		return SectionType::S_TEE;
		default:						return SectionType::S_UNDEFINED;
	}
}

CString BeamSection::_getSectionName() {
	switch (s_type)
	{
		case SectionType::S_CIRCLE:		return _T("Circle");
		case SectionType::S_RECTANGLE:	return _T("Rectangle");
		case SectionType::S_TEE:		return _T("Tee");
		default:						return _T("Undefined");
	}
}

size_t BeamSection::getNumberOfArgs() {
	switch (s_type)
	{
		case SectionType::S_CIRCLE:		return 1;
		case SectionType::S_RECTANGLE:	return 2;
		case SectionType::S_TEE:		return 4;
		default:						return 0;
	}
}

BeamSection::BeamSection(
	  const enum class SectionType s_type
	, const IsotropicMaterial material
	, const long double dataArray[]) {

	this->s_type = s_type;
	this->sectionMaterial = material;
	this->arraySize = getNumberOfArgs();
	this->sectionName = _getSectionName();

	this->dataArray = new long double[getNumberOfArgs()];
	for (size_t i = 0; i < getNumberOfArgs(); i++)
		this->dataArray[i] = dataArray[i];
}

BeamSection::~BeamSection() {
	delete[] dataArray;
}

const bool BeamSection::isValid() {
	return this->s_type == SectionType::S_UNDEFINED || this->sectionMaterial.material_type == IsotropicMaterials::NONE ? false : true;
}

long double BeamSection::getBendingIndexOfCircle() {
	long double d = dataArray[0];
	return __PI * pow(d, 3) / 32;	
}

long double BeamSection::getBendingIndexOfRectangle() {
	long double a = dataArray[0];
	long double b = dataArray[1];

	return a * pow(b, 2) / 6;
}

long double BeamSection::getBendingIndexOfTee() {
	long double a =		dataArray[0];
	long double b =		dataArray[1];
	long double t1 =	dataArray[2];
	long double t2 =	dataArray[3];

	long double A1 = a * t2; // horisontal field
	long double A2 = (b - t2) * t1; // vertical field

	long double e = (A1 * (b - t2 / 2) + A2 / 2 * (b - t2)) / (A1 + A2); // center of gravity form the bottom of tee
	long double hy_max = e > b / 2.0 ? e : b - e; // longest distance form the center to the edge of the tee

	long double alpha1 = b - t2 / 2 - e;
	long double alpha2 = e - (b - t2) / 2;

	long double Izc1 = a * pow(t2, 3) / 12;
	long double Izc2 = t1 * pow(b - t2, 3) / 12;

	long double Izc = (Izc1 + A1 * pow(alpha1, 2)) + (Izc2 + A2 * pow(alpha2, 2)); // steiner's theorem

	return Izc / hy_max;
}

long double BeamSection::getBendingIndex()
{
	switch (s_type)
	{
		case SectionType::S_CIRCLE:		return getBendingIndexOfCircle();
		case SectionType::S_RECTANGLE:	return getBendingIndexOfRectangle();
		case SectionType::S_TEE:		return getBendingIndexOfTee();
		default:						return -1;
	}
}