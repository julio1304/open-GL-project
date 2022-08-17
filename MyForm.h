#pragma once

#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glut32.lib")
//#pragma comment(lib,"glaux.lib")
#pragma comment (lib,"legacy_stdio_definitions.lib")
#include <windows.h>
#include <GL/gl.h>	
#include <GL/glu.h>	
#include "glut.h"		
int hspos = 50, vspos = 50;
void GLInit();	
void OnOpenGL();
void OnChassis();

namespace Project42 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		HDC m_hDC;
		HGLRC m_hrc;
		private: System::Windows::Forms::HScrollBar^ hScrollBar1;
	private: System::Windows::Forms::HScrollBar^ hScrollBar2;
	private: System::Windows::Forms::VScrollBar^ vScrollBar2;
	private: System::Windows::Forms::VScrollBar^ vScrollBar1;


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->hScrollBar2 = (gcnew System::Windows::Forms::HScrollBar());
			this->vScrollBar2 = (gcnew System::Windows::Forms::VScrollBar());
			this->SuspendLayout();
			// 
			// hScrollBar2
			// 
			this->hScrollBar2->Location = System::Drawing::Point(0, 9);
			this->hScrollBar2->Name = L"hScrollBar2";
			this->hScrollBar2->Size = System::Drawing::Size(1267, 21);
			this->hScrollBar2->TabIndex = 0;
			this->hScrollBar2->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &MyForm::hScrollBar2_Scroll);
			// 
			// vScrollBar2
			// 
			this->vScrollBar2->Location = System::Drawing::Point(4, 30);
			this->vScrollBar2->Name = L"vScrollBar2";
			this->vScrollBar2->Size = System::Drawing::Size(25, 541);
			this->vScrollBar2->TabIndex = 1;
			this->vScrollBar2->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &MyForm::vScrollBar2_Scroll);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1276, 571);
			this->Controls->Add(this->vScrollBar2);
			this->Controls->Add(this->hScrollBar2);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Shown += gcnew System::EventHandler(this, &MyForm::MyForm_Shown);
			this->SizeChanged += gcnew System::EventHandler(this, &MyForm::MyForm_SizeChanged);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_Shown(System::Object^ sender, System::EventArgs^ e) 
	{
		PIXELFORMATDESCRIPTOR pfd;
		pfd.dwFlags = PFD_DOUBLEBUFFER;
		m_hDC = GetDC((HWND)this->Handle.ToPointer());
		int nPixelFormat = ChoosePixelFormat(m_hDC, &pfd);
		SetPixelFormat(m_hDC, nPixelFormat, &pfd);
		m_hrc = wglCreateContext(m_hDC);
		wglMakeCurrent(m_hDC, m_hrc);

	}
	private: System::Void MyForm_SizeChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		int cx = MyForm::Size.Width;   int cy = MyForm::Size.Height;
		BOOL bResult = wglMakeCurrent(m_hDC, m_hrc);
		GLdouble gldAspect = (GLdouble)cx / (GLdouble)cy;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(30.0, gldAspect, 1.0, 10.0);   glViewport(0, 0, cx, cy);
		wglMakeCurrent(NULL, NULL);

	}
	private: System::Void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) 
	{
		wglMakeCurrent(m_hDC, m_hrc);
		GLInit();
		OnOpenGL();
		SwapBuffers(m_hDC);
		wglMakeCurrent(NULL, NULL);
	}
	private: System::Void hScrollBar2_Scroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e) 
	{
		hspos = e->NewValue;
		MyForm::Invalidate();

	}
	private: System::Void vScrollBar2_Scroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e) 
	{
		vspos = e->NewValue;
		MyForm::Invalidate();
	}
};
}

void GLInit(void)
{
	GLdouble marengo[3] = { 1.0, 1.0, 0.0 };
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
	glColor3dv(marengo);
	glScalef(0.25, 0.25, 0.25);
}

void OnOpenGL(void)
{
	glRotated(360.0 * hspos / 100, 0, 1, 0);
	glRotated(360.0 * vspos / 100, 1, 0, 0);
	glColor3f(1.0, 1.0, 0.0);//  жовтий колір
//	glutWireTeapot(1.0);
//	glutWireCube(1.0);
	OnChassis();
//	auxWireTeapot(1.0);
//	auxWireCylinder(0.3, 4.0);
}

void OnChassis(void)
{ // the base of chassis - rectangle
	glPushMatrix();  // remember the CS
	glRotatef(90.0, 1.0, 0.0, 0.0);//rotation of CS
	glColor3f(0.0, 0.5, 1.0);
	glRecti(0, 0, 6, 6);   //plane of chassis
	glPopMatrix();   // restoration of saved CS
	// wheels of chassis
	glPushMatrix(); // remember the CS
	glColor3f(1.0, 0.5, 0.0);
	glutWireTorus(0.5, 1.0,30,30); // wheel 1
	glTranslatef(6.0, 0.0, 0.0); // translation
	glutWireTorus(0.5, 1.0,30,30); // wheel 2
	glTranslatef(0.0, 0.0, 6.0); // translation
	glutWireTorus(0.5, 1.0, 30, 30); // wheel 3
	glTranslatef(-6.0, 0.0, 0.0); // translation
	glutWireTorus(0.5, 1.0, 30, 30); // wheel 4
	glPopMatrix(); // restoration of saved CS
}



