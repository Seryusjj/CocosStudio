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
int perVertexSizeInFloat = 3;  // 3+3+3+3+2

float planeSize = 1.0f;
std::vector< float > vertices =
{
	//positon								//color but used as barycentric coords in orther not to modify the renderer
	-planeSize*0.5f,  0 , -planeSize*0.5f,  1,0,0,0,
	-planeSize*0.5f,  0 ,  planeSize*0.5f,  0,1,0,0,
	 planeSize*0.5f,  0 , -planeSize*0.5f,  0,0,1,0,
	 planeSize*0.5f,  0 ,  planeSize*0.5f,  1,0,0,0,
};

MeshData::IndexArray indices =
{
	0,1,2,
	3,2,1,
};

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
	auto mesh = Mesh::create(vertices, perVertexSizeInFloat, indices, attribs);
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

void EditorGrid::draw(Renderer * renderer, const Mat4 & transform, uint32_t flags)
{
	//programState->setUniformVec4("barycentric", color);

	Sprite3D::draw(renderer, transform, flags);
}

void EditorGrid::drawGrid(int gridSize)
{
	int halfGrid = gridSize / 2;
	int count = 0;
	//from -size to 0
	for (int x = -halfGrid; x < halfGrid; x++) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(x, 0, 0);
		glVertex3f(x, 0, -halfGrid);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex3f(x, 0, 0);
		glVertex3f(x, 0, halfGrid);
		glEnd();
		count++;
		if (count % 10 == 0)
			glLineWidth(1.5f);
		else
			glLineWidth(0.5f);
	}
	count = 0;
	for (int z = -halfGrid; z < halfGrid; z++) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, 0, z);
		glVertex3f(-halfGrid, 0, z);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, 0, z);
		glVertex3f(halfGrid, 0, z);
		glEnd();
		count++;
		if (count % 10 == 0)
			glLineWidth(1.5f);
		else
			glLineWidth(0.5f);
	}
}