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

float const cellSize = 1.0f;
float const gridSize = 15;//gridSize*gridSize grid

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

const GLchar* const vShaderByteArray =
"varying vec3 vBC;\
attribute vec4 a_position;\
attribute vec4 a_color;\
\
void main() {\
	vBC = a_color.xyz;\
	gl_Position = CC_PMatrix * a_position;\
}";

const GLchar* const fShaderByteArray =
"varying vec3 vBC;\
\
float edgeFactor(){\
	vec3 d = fwidth(vec3(0,vBC.y,vBC.z));\
	vec3 a3 = smoothstep(vec3(0.0), d*1.2, vBC);\
	return min(min(a3.x, a3.y), a3.z);\
}\
\
\
void main() {\
	gl_FragColor = vec4(0.6, 0.6, 0.6, (1.0-edgeFactor())*0.95);\
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

	//setMaterial(Sprite3DMaterial::createBuiltInMaterial(Sprite3DMaterial::MaterialType::UNLIT_NOTEX, false));

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
	setOpacity(254);
	//make alpha color take effect
	//setBlendFunc(BlendFunc::ALPHA_PREMULTIPLIED);
	setCullFaceEnabled(false);
	return true;
}