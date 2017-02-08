#include "CocosGLContext.h"

static wxImage DrawDice(int size, unsigned num)
{
	wxASSERT_MSG(num >= 1 && num <= 6, wxT("invalid dice index"));

	const int dot = size / 16;        // radius of a single dot
	const int gap = 5 * size / 32;      // gap between dots

	wxBitmap bmp(size, size);
	wxMemoryDC dc;
	dc.SelectObject(bmp);
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();
	dc.SetBrush(*wxBLACK_BRUSH);

	// the upper left and lower right points
	if (num != 1)
	{
		dc.DrawCircle(gap + dot, gap + dot, dot);
		dc.DrawCircle(size - gap - dot, size - gap - dot, dot);
	}

	// draw the central point for odd dices
	if (num % 2)
	{
		dc.DrawCircle(size / 2, size / 2, dot);
	}

	// the upper right and lower left points
	if (num > 3)
	{
		dc.DrawCircle(size - gap - dot, gap + dot, dot);
		dc.DrawCircle(gap + dot, size - gap - dot, dot);
	}

	// finally those 2 are only for the last dice
	if (num == 6)
	{
		dc.DrawCircle(gap + dot, size / 2, dot);
		dc.DrawCircle(size - gap - dot, size / 2, dot);
	}

	dc.SelectObject(wxNullBitmap);

	return bmp.ConvertToImage();
}

//GLCONTEXT

CocosGLContext::CocosGLContext(wxGLCanvas *canvas)
	: wxGLContext(canvas)
{
	SetCurrent(*canvas);

	// set up the parameters we want to use
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);

	// add slightly more light, the default lighting is rather dark
	GLfloat ambient[] = { 0.5, 0.5, 0.5, 0.5 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// set viewing projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 3.0f);

	// create the textures to use for cube sides: they will be reused by all
	// canvases (which is probably not critical in the case of simple textures
	// we use here but could be really important for a real application where
	// each texture could take many megabytes)
	glGenTextures(WXSIZEOF(m_textures), m_textures);

	for (unsigned i = 0; i < WXSIZEOF(m_textures); i++)
	{
		glBindTexture(GL_TEXTURE_2D, m_textures[i]);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		const wxImage img(DrawDice(256, i + 1));

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.GetWidth(), img.GetHeight(),
			0, GL_RGB, GL_UNSIGNED_BYTE, img.GetData());
	}

	CheckGLError();
}

void CocosGLContext::DrawRotatedCube(float xangle, float yangle)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -2.0f);
	glRotatef(xangle, 1.0f, 0.0f, 0.0f);
	glRotatef(yangle, 0.0f, 1.0f, 0.0f);

	// draw six faces of a cube of size 1 centered at (0, 0, 0)
	glBindTexture(GL_TEXTURE_2D, m_textures[0]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0, 0); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, -0.5f, 0.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_textures[1]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, -0.5f, -0.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_textures[2]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0, 0); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, 0.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_textures[3]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, -0.5f, 0.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_textures[4]);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0, 0); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_textures[5]);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();

	glFlush();

	CheckGLError();
}

wxString glGetwxString(GLenum name)
{
	const GLubyte *v = glGetString(name);
	if (v == 0)
	{
		// The error is not important. It is GL_INVALID_ENUM.
		// We just want to clear the error stack.
		glGetError();

		return wxString();
	}

	return wxString((const char*)v);
}