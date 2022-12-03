#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include "Renderer.h"
#include "Utils.h"
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
	for (auto i = 0; i < vertices.size(); i++)
	{
		std::cout << vertices[i].x << ' ' << vertices[i].y << ' ' << vertices[i].z << "\n";
	}
	
	////printing the faces. For every face we print his the 3 vertecses:
	for (auto i = 0 ; i < faces.size(); i++)
	{
		std::cout << "( " << vertices[faces[i].GetVertexIndex(0)-1].x << " , " << vertices[faces[i].GetVertexIndex(0)-1].y << " , " << vertices[faces[i].GetVertexIndex(0)-1].z << " )" << "\n";
		std::cout << "( " << vertices[faces[i].GetVertexIndex(1)-1].x << " , " << vertices[faces[i].GetVertexIndex(1)-1].y << " , " << vertices[faces[i].GetVertexIndex(1)-1].z << " )" << "\n";
		std::cout << "( " << vertices[faces[i].GetVertexIndex(2)-1].x << " , " << vertices[faces[i].GetVertexIndex(2)-1].y << " , " << vertices[faces[i].GetVertexIndex(2)-1].z << " )" << "\n";
		std::cout << "\n";
	}

	// scale:
	// first we will biuld the matrix:
	/*
	*	Sx 0  0  0     x     Sx * x
	*	0  Sy 0  0  *  y  =	 Sy * y
	*	0  0  Sz 0     z     Sz * z
	*	0  0  0  1     w        w
	*/
	 
	//std::vector<glm::vec3> scale_vertices = Scale_3D(glm::ivec3(2.0f, 2.0f, 2.0f), vertices);

	// Translate:
	// first we will biuld the matrix:
	/*
	*	1  0  0  Tx     x     Tx + x
	*	0  1  0  Ty  *  y  =  Ty + y
	*	0  0  1  Tz     z     Tz + z
	*	0  0  0  1      w        w
	*/

	//std::vector<glm::vec3> scale_vertices = Translate_3D(glm::ivec3(2.0f, 2.0f, 2.0f), vertices);



	return std::make_shared<MeshModel>(faces, vertices, normals, Utils::GetFileName(filePath));
}

std::vector<glm::vec3> Utils::Scale_3D(glm::vec3 scale_vec, std::vector<glm::vec3> vertices)
{
	std::vector<glm::vec3> scale_vertices;
	glm::ivec3 temp;
	for (auto i = 0; i < vertices.size(); i++)
	{
		temp = glm::ivec3(vertices[i].x * scale_vec.x, vertices[i].y * scale_vec.y, vertices[i].z * scale_vec.z);
		scale_vertices[i] = temp;
		std::cout << vertices[i].x << ' ' << vertices[i].y << ' ' << vertices[i].z << "\n";
		std::cout << '\n';
		std::cout << scale_vertices[i].x << ' ' << scale_vertices[i].y << ' ' << scale_vertices[i].z << "\n";
	}
	return scale_vertices;
}

std::vector<glm::vec3> Utils::Translate_3D(glm::vec3 translate_vec, std::vector<glm::vec3> vertices)
{
	std::vector<glm::vec3> translate_vertices;
	glm::ivec3 temp;
	for (auto i = 0; i < vertices.size(); i++)
	{
		temp = glm::ivec3(vertices[i].x + translate_vec.x, vertices[i].y + translate_vec.y, vertices[i].z + translate_vec.z);
		translate_vertices[i] = temp;
		std::cout << vertices[i].x << ' ' << vertices[i].y << ' ' << vertices[i].z << "\n";
		std::cout << '\n';
		std::cout << translate_vertices[i].x << ' ' << translate_vertices[i].y << ' ' << translate_vertices[i].z << "\n";

	}
	return translate_vertices;
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