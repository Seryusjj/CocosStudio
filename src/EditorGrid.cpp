#include "stdafx.h"
#include "EditorGrid.h"

USING_NS_CC;

EditorGrid::EditorGrid()
{
}

EditorGrid::~EditorGrid()
{
}

std::vector< MeshVertexAttrib > attribs = {
	{ 3, GL_FLOAT, GLProgram::VERTEX_ATTRIB_POSITION,   3 * sizeof(float) },
	{ 4, GL_FLOAT, GLProgram::VERTEX_ATTRIB_COLOR,     4 * sizeof(float) },
};
int perVertexSizeInFloat = 12;  //3+4

float cellSize = 1.0f;
float gridSize = 25;//gridSize*gridSize grid

std::vector< float > vertices1;

MeshData::IndexArray indices1;

void buildVerticesAndIndices() {
	//build vertex (vertex duplied on purpose for the grid coloring)
	for (int i = -gridSize * 0.5; i < gridSize* 0.5; i++)
	{
		for (int j = -gridSize * 0.5; j < gridSize * 0.5; j++)
		{
			//first vertex
			vertices1.push_back(-cellSize*0.5f + i); vertices1.push_back(0); vertices1.push_back(-cellSize*0.5f + j);
			//barycentric coords
			vertices1.push_back(1); vertices1.push_back(0); vertices1.push_back(0); vertices1.push_back(0);

			//second vertex
			vertices1.push_back(-cellSize*0.5f + i); vertices1.push_back(0); vertices1.push_back(cellSize*0.5f + j);
			//barycentric coords
			vertices1.push_back(0);	vertices1.push_back(1);	vertices1.push_back(0);	vertices1.push_back(0);

			//third vertex
			vertices1.push_back(cellSize*0.5f + i);	vertices1.push_back(0);	vertices1.push_back(-cellSize*0.5f + j);
			//barycentric coords
			vertices1.push_back(0);	vertices1.push_back(0);	vertices1.push_back(1);	vertices1.push_back(0);

			//fourth vertex
			vertices1.push_back(cellSize*0.5f + i);	vertices1.push_back(0);	vertices1.push_back(cellSize*0.5f + j);
			//barycentric coords
			vertices1.push_back(1);	vertices1.push_back(0);	vertices1.push_back(0);	vertices1.push_back(0);
		}
	}

	int numIndex = gridSize*gridSize;
	int last = -1;
	for (int i = 0; i < numIndex; i++)
	{
		last++;
		indices1.push_back(last); indices1.push_back(last + 1);	indices1.push_back(last + 2);
		last += 3;
		indices1.push_back(last); indices1.push_back(last - 1);	indices1.push_back(last - 2);
	}
}

GLchar* vShaderByteArray =
"varying vec3 vBC;\
attribute vec4 a_position;\
attribute vec4 a_color;\
\
void main() {\
	vBC = a_color.xyz;\
	gl_Position = CC_PMatrix * a_position;\
}";

GLchar* fShaderByteArray =
"varying vec3 vBC;\
\
void main() {\
	if(any(lessThan(vBC, vec3(0.0,0.03,0.03)))){\
		gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);\
	}\
	else{\
		gl_FragColor = vec4(0.5, 0.5, 0.5, 0.0);\
	}\
}";
bool EditorGrid::init()
{
	if (!Node::init())
	{
		return false;
	}
	buildVerticesAndIndices();
	auto mesh = Mesh::create(vertices1, perVertexSizeInFloat, indices1, attribs);
	addMesh(mesh);

	setMaterial(Sprite3DMaterial::createBuiltInMaterial(Sprite3DMaterial::MaterialType::UNLIT_NOTEX, false));

	auto shaderProgram = GLProgram::createWithByteArrays(vShaderByteArray, fShaderByteArray);
	shaderProgram->link();
	shaderProgram->updateUniforms();
	shaderProgram->retain();
	//bind attributes
	shaderProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	//usead as barycentric in this particular case. We use an existing attribute so we do not have to define and update a new one.
	shaderProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	//set shader
	setGLProgram(shaderProgram);

	//make alpha color take effect
	setBlendFunc({ GL_ONE, GL_ONE_MINUS_SRC_ALPHA });

	return true;
}