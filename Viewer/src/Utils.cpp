#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include "Renderer.h"
#include "Utils.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

using namespace std;


glm::vec3 Utils::Vec3fFromStream(std::istream& issLine)
{
	float x, y, z;
	issLine >> x >> std::ws >> y >> std::ws >> z;
	return glm::vec3(x, y, z);
}

glm::vec2 Utils::Vec2fFromStream(std::istream& issLine)
{
	float x, y;
	issLine >> x >> std::ws >> y;
	return glm::vec2(x, y);
}

std::shared_ptr<MeshModel> Utils::LoadMeshModel(const std::string& filePath)
{
	std::vector<Face> faces;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::ifstream ifile(filePath.c_str());

	// while not end of file
	while (!ifile.eof())
	{
		// get line
		std::string curLine;
		std::getline(ifile, curLine);

		// read the type of the line
		std::istringstream issLine(curLine);
		std::string lineType;

		issLine >> std::ws >> lineType;

		// based on the type parse data
		if (lineType == "v")
		{
			vertices.push_back(Utils::Vec3fFromStream(issLine));
		}
		else if (lineType == "vn")
		{
			normals.push_back(Utils::Vec3fFromStream(issLine));
		}
		else if (lineType == "vt")
		{
			// TODO: Handle texture coordinates
		}
		else if (lineType == "f")
		{
			faces.push_back(Face(issLine));
		}
		else if (lineType == "#" || lineType == "")
		{
			// comment / empty line
		}
		else
		{
			std::cout << "Found unknown line Type \"" << lineType << "\"";
		}
	}

	// print
	// printing the verstecses 
	//Print_Vertices(vertices);
	//printing the faces. For every face we print his the 3 vertecses:
	//Print_Faces(vertices, faces);

	// scale:
	// first we will biuld the matrix:
	/*
	*	Sx 0  0  0     x     Sx * x
	*	0  Sy 0  0  *  y  =	 Sy * y
	*	0  0  Sz 0     z     Sz * z
	*	0  0  0  1     w        w
	*/
	// Translate:
	// first we will biuld the matrix:
	/*
	*	1  0  0  Tx     x     Tx + x
	*	0  1  0  Ty  *  y  =  Ty + y
	*	0  0  1  Tz     z     Tz + z
	*	0  0  0  1      w        w
	*/
	
	// what we did:
	// we first did traslate to make all the values positive or equal to 0, 
	// after that we used scale to make the values up to 1000
	
	/*Translations*/
	// ** Translate **
	glm::fvec3 scale_vec = glm::fvec3(vertices[0].x, vertices[0].y, vertices[0].z);
	glm::fvec3 trans_vec = glm::fvec3(vertices[0].x, vertices[0].y, vertices[0].z);
	for (int i = 0; i < vertices.size(); i++)
	{
		// min x
		if (trans_vec.x > vertices[i].x)
			trans_vec.x = vertices[i].x;
		// min y
		if (trans_vec.y > vertices[i].y)
			trans_vec.y = vertices[i].y;
		// min z
		if (trans_vec.z > vertices[i].z)
			trans_vec.z = vertices[i].z;
	}
	float min = trans_vec.x;
	if (trans_vec.y < min)
		min = trans_vec.y;
	if (trans_vec.z < min)
		min = trans_vec.z;
	if (min < 0)
	{
		min *= (-1.0f);
		trans_vec.x = min; trans_vec.y = min; trans_vec.z = min;

		for (auto i = 0; i < vertices.size(); i++)
		{
			float x = vertices[i].x + min, y=vertices[i].y + min, z= vertices[i].z + min;
			vertices[i] = glm::fvec3(vertices[i].x + min, vertices[i].y + min, vertices[i].z + min);
		}
	}
	// ** Scale ** 
	for (int i = 0; i < vertices.size(); i++)
	{
		// max x
		if (scale_vec.x < vertices[i].x)
			scale_vec.x = vertices[i].x;
		// max y
		if (scale_vec.y < vertices[i].y)
			scale_vec.y = vertices[i].y;
		// max z
		if (scale_vec.z < vertices[i].z)
			scale_vec.z = vertices[i].z;
	}
	float max = scale_vec.x;
	if (scale_vec.y > max)
		max = scale_vec.y;
	if (scale_vec.z > max)
		max = scale_vec.z;
	scale_vec.x = 1000 / max; scale_vec.y = 1000 / max; scale_vec.z = 1000 / max;
	for (auto i = 0; i < vertices.size(); i++)
	{
		vertices[i] = glm::fvec3(vertices[i].x * scale_vec.x, vertices[i].y * scale_vec.y, vertices[i].z * scale_vec.z);
	}

	return std::make_shared<MeshModel>(faces, vertices, normals, Utils::GetFileName(filePath));
}

void Utils::Print_Vertices(std::vector<glm::vec3> vertices)
{
	for (auto i = 0; i < vertices.size(); i++)
	{
		std::cout << vertices[i].x << ' ' << vertices[i].y << ' ' << vertices[i].z << "\n";
	}
}

void Utils::Print_Faces(std::vector<glm::vec3> vertices, std::vector<Face> faces)
{
	for (auto i = 0; i < faces.size(); i++)
	{
		std::cout << "( " << vertices[faces[i].GetVertexIndex(0)-1].x << " , " << vertices[faces[i].GetVertexIndex(0)-1].y << " , " << vertices[faces[i].GetVertexIndex(0)-1].z << " )" << "\n";
		std::cout << "( " << vertices[faces[i].GetVertexIndex(1)-1].x << " , " << vertices[faces[i].GetVertexIndex(1)-1].y << " , " << vertices[faces[i].GetVertexIndex(1)-1].z << " )" << "\n";
		std::cout << "( " << vertices[faces[i].GetVertexIndex(2)-1].x << " , " << vertices[faces[i].GetVertexIndex(2)-1].y << " , " << vertices[faces[i].GetVertexIndex(2)-1].z << " )" << "\n";
		std::cout << "\n";
	}
}






std::string Utils::GetFileName(const std::string& filePath)
{
	if (filePath.empty()) {
		return {};
	}

	auto len = filePath.length();
	auto index = filePath.find_last_of("/\\");

	if (index == std::string::npos) {
		return filePath;
	}

	if (index + 1 >= len) {

		len--;
		index = filePath.substr(0, len).find_last_of("/\\");

		if (len == 0) {
			return filePath;
		}

		if (index == 0) {
			return filePath.substr(1, len - 1);
		}

		if (index == std::string::npos) {
			return filePath.substr(0, len);
		}

		return filePath.substr(index + 1, len - index - 1);
	}

	return filePath.substr(index + 1, len - index);
}