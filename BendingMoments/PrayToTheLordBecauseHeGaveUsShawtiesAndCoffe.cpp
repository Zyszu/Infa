#include "pch.h"
#include "PrayToTheLordBecauseHeGaveUsShawtiesAndCoffe.h"

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

// doesn't work for e = 0
long double ld_pow(const long double& n, size_t e) {
	long double _ret = n;
	for (size_t i = 0; i < e - 1; i++)
		_ret *= n;
	return _ret;
}

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

long double* getDefaultValues(const enum class SectionType s_type) {
	switch (s_type)
	{
	case SectionType::S_CIRCLE: {
		long double arr[1] = { 15 };
		return arr;
	}
	case SectionType::S_RECTANGLE: {
		long double arr[2] = { 15, 15 };
		return arr;
	}
	case SectionType::S_TEE: {
		long double arr[4] = { 15, 15, 4, 4 };
		return arr;
	}
	default: return NULL;
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
	, const long double* _dataArray) {

	this->s_type = s_type;
	this->arraySize = getNumberOfArgs();

	this->dataArray = new long double[this->arraySize];
	for (size_t i = 0; i < this->arraySize; i++)
		this->dataArray[i] = _dataArray[i];
}

BeamSection::~BeamSection() {
	delete dataArray;
}

long double BeamSection::getBendingIndexOfCircle() {
	long double d = this->dataArray[0];
	return __PI * ld_pow(d, 3) / 32;
}

long double BeamSection::getBendingIndexOfRectangle() {
	long double a = this->dataArray[0];
	long double b = this->dataArray[1];

	return a * ld_pow(b, 2) / 6;
}

long double BeamSection::getBendingIndexOfTee() {
	long double a = this->dataArray[0];
	long double b = this->dataArray[1];
	long double t1 = this->dataArray[2];
	long double t2 = this->dataArray[3];

	long double A1 = a * t2; // horisontal field
	long double A2 = (b - t2) * t1; // vertical field

	long double e = (A1 * (b - t2 / 2) + A2 / 2 * (b - t2)) / (A1 + A2); // center of gravity form the bottom of tee
	long double hy_max = e > b / 2.0 ? e : b - e; // longest distance form the center to the edge of the tee

	long double alpha1 = b - t2 / 2 - e;
	long double alpha2 = e - (b - t2) / 2;

	long double Izc1 = a * ld_pow(t2, 3) / 12;
	long double Izc2 = t1 * ld_pow(b - t2, 3) / 12;

	long double Izc = (Izc1 + A1 * ld_pow(alpha1, 2)) + (Izc2 + A2 * ld_pow(alpha2, 2)); // steiner's theorem

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

const bool Beam::isValid() {
	return this->section.s_type == SectionType::S_UNDEFINED || this->material.material_type == IsotropicMaterials::NONE ? false : true;
}