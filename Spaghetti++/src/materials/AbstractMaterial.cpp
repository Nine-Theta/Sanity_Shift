#include "materials/AbstractMaterial.hpp"
namespace sge {
	AbstractMaterial::AbstractMaterial()
	{
		//ctor
	}

	AbstractMaterial::~AbstractMaterial()
	{
		//dtor
	}
	unsigned AbstractMaterial::_renderedPolys = 0;
	unsigned AbstractMaterial::GetRenderedPolys()
	{
		unsigned polys = _renderedPolys;
		_renderedPolys = 0;
		return polys;
	}

}