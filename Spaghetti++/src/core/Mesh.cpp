#pragma once
#include <iostream>
#include <map>
#include <string>
#include <fstream>

#include "core/Mesh.hpp"
namespace sge {
	using namespace glm;
	Mesh::Mesh() : _indexBufferId(0), _vertexBufferId(0), _normalBufferId(0), _uvBufferId(0), _vertices(), _normals(), _uvs(), _indices()
	{
		//ctor
	}

	Mesh::~Mesh()
	{
		//dtor
	}

	/**
	 * Load reads the obj data into a new mesh using C++ combined with c style coding.
	 * The result is an indexed mesh for use with glDrawElements.
	 * Expects a obj file with following layout v/vt/vn/f eg
	 *
	 * For example the obj file for a simple plane describes two triangles, based on
	 * four vertices, with 4 uv's all having the same vertex normals (NOT FACE NORMALS!)
	 *
	 * v 10.000000 0.000000 10.000000              //vertex 1
	 * v -10.000000 0.000000 10.000000             //vertex 2
	 * v 10.000000 0.000000 -10.000000             //vertex 3
	 * v -10.000000 0.000000 -10.000000            //vertex 4
	 * vt 0.000000 0.000000                        //uv 1
	 * vt 1.000000 0.000000                        //uv 2
	 * vt 1.000000 1.000000                        //uv 3
	 * vt 0.000000 1.000000                        //uv 4
	 * vn 0.000000 1.000000 -0.000000              //normal 1 (normal for each vertex is same)
	 * s off
	 *
	 * Using these vertices, uvs and normals we can construct faces, made up of 3 triplets (vertex, uv, normal)
	 * f 2/1/1 1/2/1 3/3/1                         //face 1 (triangle 1)
	 * f 4/4/1 2/1/1 3/3/1                         //face 2 (triangle 2)
	 *
	 * So although this is a good format for blender and other tools reading .obj files, this is
	 * not an index mechanism that OpenGL supports out of the box.
	 * The reason is that OpenGL supports only one indexbuffer, and the value at a certain point in the indexbuffer, eg 3
	 * refers to all three other buffers (v, vt, vn) at once,
	 * eg if index[0] = 5, opengl will stream vertexBuffer[5], uvBuffer[5], normalBuffer[5] into the shader.
	 *
	 * So what we have to do after reading the file with all vertices, is construct unique indexes for
	 * all pairs that are described by the faces in the object file, eg if you have
	 * f 2/1/1 1/2/1 3/3/1                         //face 1 (triangle 1)
	 * f 4/4/1 2/1/1 3/3/1                         //face 2 (triangle 2)
	 *
	 * v/vt/vn[0] will represent 2/1/1
	 * v/vt/vn[1] will represent 1/2/1
	 * v/vt/vn[2] will represent 3/3/1
	 * v/vt/vn[3] will represent 4/4/1
	 *
	 * and that are all unique pairs, after which our index buffer can contain:
	 *
	 * 0,1,2,3,0,2
	 *
	 * So the basic process is, read ALL data into separate arrays, then use the faces to
	 * create unique entries in a new set of arrays and create the indexbuffer to go along with it.
	 *
	 * Note that loading this mesh isn't cached like we do with texturing, this is an exercise left for the students.
	 */
	Mesh* Mesh::load(std::string pFilename)
	{
		std::cout << "Loading " << pFilename << "...";

		Mesh* mesh = new Mesh();

		std::ifstream file(pFilename, std::ios::in);

		if (file.is_open()) {
			//these three vectors will contains data as taken from the obj file
			//in the order it is encountered in the object file
			std::vector<glm::vec3> vertices;
			std::vector<glm::vec3> normals;
			std::vector<glm::vec3> tangents;
			std::vector<glm::vec2> uvs;

			//in addition we create a map to store the triplets found under the f(aces) section in the
			//object file and map them to an index for our index buffer (just number them sequentially
			//as we encounter them and store references to the pack
			std::map <FaceIndexTriplet, unsigned int> mappedTriplets;

			std::string line; // to store each line in
			while (getline(file, line)) {

				// c-type string to store cmd read from obj file (cmd is v, vt, vn, f)
				char cmd[10];
				cmd[0] = 0;

				//get the first string in the line of max 10 chars (c-style)
				sscanf(line.c_str(), "%10s", cmd);

				//note that although the if statements below seem to imply that we can
				//read these different line types (eg vertex, normal, uv) in any order,
				//this is just convenience coding for us (instead of multiple while loops)
				//we assume the obj file to list ALL v lines first, then ALL vt lines,
				//then ALL vn lines and last but not least ALL f lines last

				//so... start processing lines
				//are we reading a vertex line? straightforward copy into local vertices vector
				if (strcmp(cmd, "v") == 0) {
					glm::vec3 vertex;
					sscanf(line.c_str(), "%10s %f %f %f ", cmd, &vertex.x, &vertex.y, &vertex.z);
					vertices.push_back(vertex);

					//or are we reading a normal line? straightforward copy into local normal vector
				}
				else if (strcmp(cmd, "vn") == 0) {
					glm::vec3 normal;
					sscanf(line.c_str(), "%10s %f %f %f ", cmd, &normal.x, &normal.y, &normal.z);
					normals.push_back(normal);

					//or are we reading a uv line? straightforward copy into local uv vector
				}
				else if (strcmp(cmd, "vt") == 0) {
					glm::vec2 uv;
					sscanf(line.c_str(), "%10s %f %f ", cmd, &uv.x, &uv.y);
					uvs.push_back(uv);

					//this is where it gets nasty. After having read all vertices, normals and uvs into
					//their own buffer
				}
				else if (strcmp(cmd, "f") == 0) {

					//an f lines looks like
					//f 2/1/1 1/2/1 3/3/1
					//in other words
					//f v1/u1/n1 v2/u2/n2 v3/u3/n3
					//for each triplet like that we need to check whether we already encountered it
					//and update our administration based on that
					glm::ivec3 vertexIndex;
					glm::ivec3 normalIndex;
					glm::ivec3 uvIndex;
					int count = sscanf(line.c_str(), "%10s %d/%d/%d %d/%d/%d %d/%d/%d", cmd, &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

					//Have we read exactly 10 elements?
					if (count == 10) {

						//process 3 triplets, one for each vertex (which is first element of the triplet)
						for (int i = 0; i < 3; ++i) {
							//create key out of the triplet and check if we already encountered this before
							FaceIndexTriplet triplet(vertexIndex[i], uvIndex[i], normalIndex[i]);
							std::map<FaceIndexTriplet, unsigned int>::iterator found = mappedTriplets.find(triplet);

							//if iterator points at the end, we haven't found it
							if (found == mappedTriplets.end())
							{
								//so create a new index value, and map our triplet to it
								unsigned int index = mappedTriplets.size();
								mappedTriplets[triplet] = index;

								//now record this index
								mesh->_indices.push_back(index);
								//and store the corresponding vertex/normal/uv values into our own buffers
								//note the -1 is required since all values in the f triplets in the .obj file
								//are 1 based, but our vectors are 0 based
								mesh->_vertices.push_back(vertices[vertexIndex[i] - 1]);
								mesh->_normals.push_back(normals[normalIndex[i] - 1]);
								mesh->_uvs.push_back(uvs[uvIndex[i] - 1]);
							}
							else
							{
								//if the key was already present, get the index value for it
								unsigned int index = found->second;
								//and update our index buffer with it
								mesh->_indices.push_back(index);
							}
						}
					}
					else {
						//If we read a different amount, something is wrong
						std::cout << "Error reading obj, needing v,vn,vt" << std::endl;
						delete mesh;
						return NULL;
					}
				}

			}

			file.close();
			mesh->_makeTangents();
			mesh->_buffer();

			std::cout << "Mesh loaded and buffered:" << (mesh->_indices.size() / 3.0f) << " triangles." << std::endl;
			return mesh;
		}
		else {
			std::cout << "Could not read " << pFilename << std::endl;
			delete mesh;
			return NULL;
		}
	}

	void Mesh::_buffer()
	{
		glGenBuffers(1, &_indexBufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

		glGenBuffers(1, &_vertexBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
		glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), &_vertices[0], GL_STATIC_DRAW);

		glGenBuffers(1, &_normalBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, _normalBufferId);
		glBufferData(GL_ARRAY_BUFFER, _normals.size() * sizeof(glm::vec3), &_normals[0], GL_STATIC_DRAW);

		glGenBuffers(1, &_tangentBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, _tangentBufferId);
		glBufferData(GL_ARRAY_BUFFER, _tangents.size() * sizeof(glm::vec3), &_tangents[0], GL_STATIC_DRAW);

		glGenBuffers(1, &_uvBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, _uvBufferId);
		glBufferData(GL_ARRAY_BUFFER, _uvs.size() * sizeof(glm::vec2), &_uvs[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	vec3 _boundingBox[] = { vec3(0,0,0),vec3(0,0,0),vec3(0,0,0),vec3(0,0,0),vec3(0,0,0),vec3(0,0,0),vec3(0,0,0),vec3(0,0,0) };

	void Mesh::_makeTangents()
	{
		vec2 boundsX;
		vec2 boundsY;
		vec2 boundsZ;
		_tangents.resize(_normals.size());
		printf("Making mesh tangents...\n");
		for (int i = 0; i < _indices.size(); i += 3) {
			vec3 normal1 = _normals[_indices[i]];
			vec3 normal2 = _normals[_indices[i + 1]];
			vec3 normal3 = _normals[_indices[i + 2]];
			
			vec3 pos1 = _vertices[_indices[i]];
			vec3 pos2 = _vertices[_indices[i + 1]];
			vec3 pos3 = _vertices[_indices[i + 2]];

			vec2 uv1 = _uvs[_indices[i]];
			vec2 uv2 = _uvs[_indices[i + 1]];
			vec2 uv3 = _uvs[_indices[i + 2]];

			boundsX.x = min(boundsX.x, pos1.x);
			boundsX.y = max(boundsX.y, pos1.x);
			boundsX.x = min(boundsX.x, pos2.x);
			boundsX.y = max(boundsX.y, pos2.x);
			boundsX.x = min(boundsX.x, pos3.x);
			boundsX.y = max(boundsX.y, pos3.x);

			boundsY.x = min(boundsY.x, pos1.y);
			boundsY.y = max(boundsY.y, pos1.y);
			boundsY.x = min(boundsY.x, pos2.y);
			boundsY.y = max(boundsY.y, pos2.y);
			boundsY.x = min(boundsY.x, pos3.y);
			boundsY.y = max(boundsY.y, pos3.y);

			boundsZ.x = min(boundsZ.x, pos1.z);
			boundsZ.y = max(boundsZ.y, pos1.z);
			boundsZ.x = min(boundsZ.x, pos2.z);
			boundsZ.y = max(boundsZ.y, pos2.z);
			boundsZ.x = min(boundsZ.x, pos3.z);
			boundsZ.y = max(boundsZ.y, pos3.z);

			vec3 tan1 = normalize(pos2 - pos1);
			vec2 uvd1 = normalize(uv2 - uv1);
			float rd1 = -acos(dot(uvd1, vec2(0, 1)));
			mat3 mrot;
			mrot[2] = normal1;
			mrot[0] = normalize(cross(mrot[2], mrot[2].y == 1 || mrot[2].y == -1 ? vec3(0, 0.9, -0.05) : vec3(0,1,0)));
			mrot[1] = normalize(cross(mrot[2], mrot[0]));
			tan1 = inverse(mrot) * tan1;
			float sign = dot(uvd1, vec2(1, 0)) < 0 ? 1 : -1;
			glm::mat3 trot = rotate(glm::mat4(), rd1 * sign, vec3(0,0,1));
//			mat3 trot;
			tan1 = trot * tan1;
			tan1 = mrot * tan1;
			_tangents[_indices[i]] = normalize(tan1);



			vec3 tan2 = normalize(pos3 - pos2);
			vec2 uvd2 = normalize(uv3 - uv2);
			float rd2 = -acos(dot(uvd2, vec2(0, 1)));
			mrot;
			mrot[2] = normal1;
			mrot[0] = normalize(cross(mrot[2], mrot[2].y == 1 || mrot[2].y == -1 ? vec3(0, 0.9, -0.05) : vec3(0, 1, 0)));
			mrot[1] = normalize(cross(mrot[2], mrot[0]));
			tan2 = inverse(mrot) * tan2;
			sign = dot(uvd2, vec2(1, 0)) < 0 ? 1 : -1;
			trot = rotate(glm::mat4(), rd2 * sign, vec3(0, 0, 1));
			tan2 = trot * tan2;
			tan2 = mrot * tan2;
			_tangents[_indices[i + 1]] = normalize(tan2);

			vec3 tan3 = normalize(pos1 - pos3);
			vec2 uvd3 = normalize(uv1 - uv3);
			float rd3 = -acos(dot(uvd3, vec2(0, 1)));
			mrot;
			mrot[2] = normal1;
			mrot[0] = normalize(cross(mrot[2], mrot[2].y == 1 || mrot[2].y == -1 ? vec3(0, 0.9, -0.05) : vec3(0, 1, 0)));
			mrot[1] = normalize(cross(mrot[2], mrot[0]));
			tan3 = inverse(mrot) * tan3;
			sign = dot(uvd3, vec2(1, 0)) < 0 ? 1 : -1;
			trot = rotate(glm::mat4(), rd3 * sign, vec3(0, 0, 1));
			tan3 = trot * tan3;
			tan3 = mrot * tan3;
			_tangents[_indices[i + 2]] = normalize(tan3);
		}

		std::cout << "Building bounding box..." << std::endl;
		_boundingBox[0] = vec3(boundsX.x, boundsY.x, boundsZ.x);
		_boundingBox[1] = vec3(boundsX.x, boundsY.x, boundsZ.y);
		_boundingBox[2] = vec3(boundsX.x, boundsY.y, boundsZ.x);
		_boundingBox[3] = vec3(boundsX.x, boundsY.y, boundsZ.y);
		_boundingBox[4] = vec3(boundsX.y, boundsY.x, boundsZ.x);
		_boundingBox[5] = vec3(boundsX.y, boundsY.x, boundsZ.y);
		_boundingBox[6] = vec3(boundsX.y, boundsY.y, boundsZ.x);
		_boundingBox[7] = vec3(boundsX.y, boundsY.y, boundsZ.y);
	}

	void Mesh::streamToOpenGL(GLint pVerticesAttrib, GLint pNormalsAttrib, GLint pUVsAttrib) {
		if (pVerticesAttrib != -1) {
			glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
			glEnableVertexAttribArray(pVerticesAttrib);
			glVertexAttribPointer(pVerticesAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		if (pNormalsAttrib != -1) {
			glBindBuffer(GL_ARRAY_BUFFER, _normalBufferId);
			glEnableVertexAttribArray(pNormalsAttrib);
			glVertexAttribPointer(pNormalsAttrib, 3, GL_FLOAT, GL_TRUE, 0, 0);
		}

		if (pUVsAttrib != -1) {
			glBindBuffer(GL_ARRAY_BUFFER, _uvBufferId);
			glEnableVertexAttribArray(pUVsAttrib);
			glVertexAttribPointer(pUVsAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferId);

		glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, (GLvoid*)0);

		// no current buffer, to avoid mishaps, very important for performance

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//fix for serious performance issue
		if (pUVsAttrib != -1) glDisableVertexAttribArray(pUVsAttrib);
		if (pNormalsAttrib != -1) glDisableVertexAttribArray(pNormalsAttrib);
		if (pVerticesAttrib != -1) glDisableVertexAttribArray(pVerticesAttrib);
	}

	void Mesh::streamToOpenGL(GLint pVerticesAttrib, GLint pNormalsAttrib, GLint pTangentAttrib, GLint pUVsAttrib)
	{
		if (pVerticesAttrib != -1) {
			glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
			glEnableVertexAttribArray(pVerticesAttrib);
			glVertexAttribPointer(pVerticesAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		if (pNormalsAttrib != -1) {
			glBindBuffer(GL_ARRAY_BUFFER, _normalBufferId);
			glEnableVertexAttribArray(pNormalsAttrib);
			glVertexAttribPointer(pNormalsAttrib, 3, GL_FLOAT, GL_TRUE, 0, 0);
		}

		if (pTangentAttrib != -1) {
			glBindBuffer(GL_ARRAY_BUFFER, _tangentBufferId);
			glEnableVertexAttribArray(pTangentAttrib);
			glVertexAttribPointer(pTangentAttrib, 3, GL_FLOAT, GL_TRUE, 0, 0);
		}

		if (pUVsAttrib != -1) {
			glBindBuffer(GL_ARRAY_BUFFER, _uvBufferId);
			glEnableVertexAttribArray(pUVsAttrib);
			glVertexAttribPointer(pUVsAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferId);

		glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, (GLvoid*)0);

		// no current buffer, to avoid mishaps, very important for performance

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//fix for serious performance issue
		//if (pUVsAttrib != -1) glDisableVertexAttribArray(pUVsAttrib);
		//if (pNormalsAttrib != -1) glDisableVertexAttribArray(pNormalsAttrib);
		//if (pTangentAttrib != -1) glDisableVertexAttribArray(pTangentAttrib);
		//if (pVerticesAttrib != -1) glDisableVertexAttribArray(pVerticesAttrib);
	}

	void Mesh::drawDebugInfo(const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
		//demo of how to render some debug info using the good ol' direct rendering mode...
		if (_indices.size() > 500000) return;
		glUseProgram(0);
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(glm::value_ptr(pProjectionMatrix));
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(glm::value_ptr(pViewMatrix * pModelMatrix));

		glBegin(GL_LINES);
		//for each index draw the normal starting at the corresponding vertex
		for (size_t i = 0; i < _indices.size(); i++) {
			//draw normal for vertex
			if (true) {
				//now get normal end
				glm::vec3 normal = _normals[_indices[i]];
				//glColor3fv(glm::value_ptr(normal));
				glColor3f(0,0,1);

				glm::vec3 normalStart = _vertices[_indices[i]];
				glVertex3fv(glm::value_ptr(normalStart));
				glm::vec3 normalEnd = normalStart + normal * 0.03f;
				glVertex3fv(glm::value_ptr(normalEnd));

				glm::vec3 tangent = _tangents[_indices[i]];
				//glColor3fv(glm::value_ptr(tangent));
				glColor3f(0, 1, 0);

				glm::vec3 tangentStart = _vertices[_indices[i]];
				glVertex3fv(glm::value_ptr(tangentStart));
				glm::vec3 tangentEnd = tangentStart + tangent * 0.03f;
				glVertex3fv(glm::value_ptr(tangentEnd));
			}

		}
		glEnd();
	}
	std::vector<unsigned int>& Mesh::GetIndices()
	{
		return _indices;
	}
	std::vector<glm::vec3>& Mesh::GetVertices()
	{
		return _vertices;
	}
	vec3* Mesh::GetBoundingBox()
	{
		return _boundingBox;
	}
	unsigned Mesh::GetPolyCount()
	{
		return _indices.size() / 3.0f;
	}
}


