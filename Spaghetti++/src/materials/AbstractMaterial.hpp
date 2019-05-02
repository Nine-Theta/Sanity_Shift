#pragma once
#ifndef ABSTRACTMATERIAL_HPP
#define ABSTRACTMATERIAL_HPP

#include "glm/glm.hpp"
//#include "components/MeshComponent.h"
#include "components/CameraComponent.h"
//#include "core/Mesh.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace sge {
	class GameObject;
	class Mesh;
	class World;
	class MeshComponent;

	/**
	 * AbstractMaterial should be subclassed for all materials, for example ColorMaterial, TextureMaterial.
	 *
	 * Basically a material is responsible for setting up the correct shader,
	 * filling all the correct parameters and actually rendering a mesh by streaming all mesh data through a
	 * specific shader. Subclasses often use a static shader variable which is initialized once upon first use,
	 * but that is fully optional (!).
	 *
	 * This works like the Unity Material, where you have to select a shader for a material and the shader chosen
	 * determines which properties actually become available for the material itself.
	 */
	class AbstractMaterial
	{
	public:
		AbstractMaterial();
		virtual ~AbstractMaterial();

		/**
		 * Render the given mesh in the given world using the given mvp matrices. Implement in subclass.
		 */
		virtual void render(MeshComponent* mesh, CameraComponent* cam = NULL) = 0;
		static unsigned GetRenderedPolys();
	protected:
		static unsigned _renderedPolys;
	};
}

#endif // ABSTRACTMATERIAL_HPP
