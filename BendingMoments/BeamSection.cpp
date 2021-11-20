#include "pch.h"
#include "BeamSection.h"


long double TeeSection::getBendingIndex() const
{
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

BeamSection StdBeamSections::getSection(enum class Sections section) {
	switch (section)
	{
	case Sections::NNONE:		return NotASeciton();
	case Sections::CIRCLE:		return CircleSection();
	case Sections::RECTANGLE:	return RectangleSeciton();
	case Sections::TEE:			return TeeSection();
	default:					return NotASeciton();
	}
}