#pragma once
#include "IsotropicMaterial.h"
#include <math.h>

#define __PI 3.14159265

enum class sectionType : int
{
	S_UNDEFINED,
	S_CIRCLE,
	S_RECTANGLE,
	S_TEE
};

class _BeamSection
{
public:
	CString sectionName;
	sectionType s_type;
	IsotropicMaterial sectionMaterial;
	size_t arraySize;
	long double* dataArray;

	CString getSectionName()
	{
		switch (s_type)
		{
			case sectionType::S_CIRCLE:		return _T("Circle");
			case sectionType::S_RECTANGLE:	return _T("Rectangle");
			case sectionType::S_TEE:		return _T("Tee");
			default:						return _T("Undefined");
		}
	}

	size_t getNumberOfArgs() 
	{
		switch (s_type)
		{
			case sectionType::S_CIRCLE:		return 1;
			case sectionType::S_RECTANGLE:	return 2;
			case sectionType::S_TEE:		return 4;
			default:						return 0;
		}
	}

	void dataArrayFill(va_list& list)
	{
		for (size_t i = 0; i < arraySize; i++)
		{
			dataArray[i] = va_arg(list, long double);
		}
		va_end(list);
	}

	_BeamSection(const enum class sectionType s_type, const IsotropicMaterial material, ...)
	{
		va_list values;
		
		this->s_type = s_type;
		this->sectionMaterial = material;
		this->arraySize = getNumberOfArgs();
		this->sectionName = getSectionName();

		dataArray = (long double*) malloc(arraySize * sizeof(long double));
		va_start(values, arraySize);

		dataArrayFill(values);
	}



private:
	long double getBendingIndexOfCircle() {
		long double d = dataArray[0];
		return __PI * pow(d, 3)/32;
	}

	long double getBendingIndexOfRectangle() {
		long double a = dataArray[0];
		long double b = dataArray[1];

		return a * pow(b, 2) / 6;
	}

	long double getBendingIndexOfTee() {
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



public:
	long double getBendingIndex()
	{
		switch (s_type)
		{
			case sectionType::S_CIRCLE:		return getBendingIndexOfCircle();
			case sectionType::S_RECTANGLE:	return getBendingIndexOfRectangle();
			case sectionType::S_TEE:		return getBendingIndexOfTee();
			default:						return -1;
		}
	}
};


class BeamSection
{
public:
	IsotropicMaterial isotropicMaterial;
	CString name;
	bool iAmNotASeciton;
	long double d;
	long double a;
	long double b;
	long double t1;
	long double t2;

	long double getBendingIndex() { return 0; }
};

class NotASeciton : public BeamSection
{
public:
	NotASeciton()
	{
		this->iAmNotASeciton = true;
	}
};

class CircleSection : public BeamSection
{
public:
	long double r;

	CircleSection(
		  const IsotropicMaterial& material = StdBeamMaterials::steel
		, const long double& radius = 10)
	{
		this->name = (CString)"Circle";
		this->isotropicMaterial = material;
		this->r = radius;
	}

	long double getBendingIndex() const
	{
		return __PI * pow(r, 3);
	}
};

class RectangleSeciton : public BeamSection
{
public:
	long double a;
	long double b;

	RectangleSeciton(
		  const IsotropicMaterial& material = StdBeamMaterials::steel
		, const long double& a = 10
		, const long double& b = 10)
	{
		this->name = (CString)"Rectangle";
		this->isotropicMaterial = material;
		this->a = a;
		this->b = b;
	}

	long double getBendingIndex() const
	{
		return a * pow(b, 2) / 6;
	}
};

class TeeSection : public BeamSection
{
public:
	long double a;
	long double b;
	long double t1;
	long double t2;

	TeeSection(
		  const IsotropicMaterial& material = StdBeamMaterials::steel
		, const long double& a = 10
		, const long double& b = 10
		, const long double& t1 = 4
		, const long double& t2 = 4)
	{
		this->name = (CString)"Tee";
		this->isotropicMaterial = material;
		this->a = a;
		this->b = b;
		this->t1 = t1;
		this->t2 = t2;
	}

	long double getBendingIndex() const;
};

namespace StdBeamSections
{
	enum class Sections : int
	{
		NNONE = -1,
		CIRCLE,
		RECTANGLE,
		TEE
	};

	BeamSection getSection(enum class Sections section);
}