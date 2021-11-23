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

size_t getNumberOfArgs(const enum class SectionType s_type) {
	switch (s_type)
	{
		case SectionType::S_CIRCLE:		return 1;
		case SectionType::S_RECTANGLE:	return 2;
		case SectionType::S_TEE:		return 4;
		default:						return 0;
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
	switch (this->s_type)
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

	if (!this->arraySize == 0) {
		this->dataArray = new long double[this->arraySize];
		for (size_t i = 0; i < this->arraySize; i++)
			this->dataArray[i] = _dataArray[i];
	} 
}

BeamSection::BeamSection() {
	this->arraySize = 0;
	this->s_type = SectionType::S_UNDEFINED;
	this->dataArray = NULL;
}

BeamSection::~BeamSection() {
	// it's crucial for program to work good but it's generating errors so I commended it for now
	//if (!this->arraySize == 0) delete[] this->dataArray;
}

long double BeamSection::getBendingIndexOfCircle() {
	long double d = this->dataArray[0];
	return __PI * ld_pow(d, 3) / 32.0L;
}

long double BeamSection::getBendingIndexOfRectangle() {
	long double a = this->dataArray[0];
	long double b = this->dataArray[1];

	return a * ld_pow(b, 2) / 6.0L;
}

long double BeamSection::getBendingIndexOfTee() {
	long double a = this->dataArray[0];
	long double b = this->dataArray[1];
	long double t1 = this->dataArray[2];
	long double t2 = this->dataArray[3];

	long double A1 = a * t2; // horisontal field
	long double A2 = (b - t2) * t1; // vertical field

	long double e = (A1 * (b - t2 / 2.0L) + A2 / 2 * (b - t2)) / (A1 + A2); // center of gravity form the bottom of tee
	long double hy_max = e > b / 2.0L ? e : b - e; // longest distance form the center to the edge of the tee

	long double alpha1 = b - t2 / 2.0L - e; // check here <<<<<<<<<<<-------------------------------------------------
	long double alpha2 = e - (b - t2) / 2.0L;

	long double Izc1 = a * ld_pow(t2, 3) / 12.0L;
	long double Izc2 = t1 * ld_pow(b - t2, 3) / 12.0L;

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

const SectionType BeamSection::getSectionType() {
	switch (this->s_type)
	{
		case SectionType::S_CIRCLE:		return SectionType::S_CIRCLE;
		case SectionType::S_RECTANGLE:	return SectionType::S_RECTANGLE;
		case SectionType::S_TEE:		return SectionType::S_TEE;
		default:						return SectionType::S_UNDEFINED;
	}
}

const bool Beam::isValid() {
	return this->section.getSectionType() == SectionType::S_UNDEFINED || this->material.material_type == IsotropicMaterials::NONE ? false : true;
}

Beam::Beam(const BeamSection _section, const IsotropicMaterial _material, const long double& length) {
	this->section = _section;
	this->material = _material;
	this->length = length;
}

Beam::Beam() {
	this->material = IsotropicMaterial();
	this->section = BeamSection();
	this->length = 0;
}

const long double Beam::getMaxBendingMoment(const long double& point, const long double& force) {
	return ((1.0L - (point / this->length)) * force) * point;
}

const long double Beam::getDefleftionAt(const long double& f_point, const long double& d_point, const long double& force) {
	long double Ra = (1 - (f_point / this->length)) * force;
	long double prefix = 1.0L / (this->material.youngModulus * this->section.getBendingIndex());
	
	if (d_point < f_point) {
		long double inside1 = (1.0L / 6.0L) * ld_pow(d_point, 3) * Ra;
		long double inside2 = (.5L) * Ra * ld_pow(f_point, 2) * d_point;
		long double inside3 = (.25L) * force * ld_pow(f_point, 2) * d_point;
		return prefix * (inside1 - inside2 - inside3);
	}
	else {
		long double inside1 = (1.0L / 6.0L) * ld_pow(d_point, 3) * Ra;
		long double inside2 = (1.0L / 6.0L) * ld_pow(d_point, 3) * force;
		long double inside3 = (.5L) * ld_pow(d_point, 2) * f_point * force;
		long double inside4 = (.5L) * Ra * ld_pow(f_point, 2) * d_point;
		long double inside5 = (.25L) * force * ld_pow(f_point, 2) * d_point;
		long double Di1 = (1.0L / 6.0L) * force * ld_pow(this->length, 3);
		long double Di2 = (.5L) * ld_pow(f_point, 2) * Ra * this->length;
		long double Di3 = (.25L) * ld_pow(f_point, 2) * force * this->length;
		long double Di4 = (1.0L / 6.0L) * Ra * ld_pow(this->length, 3);
		long double Di5 = (.5L) * f_point * force * ld_pow(this->length, 2);

		long double D = Di1 + Di2 + Di3 - Di4 - Di5;

		return prefix * (inside1 - inside2 + inside3 - inside4 - inside5 + D);
	}
}