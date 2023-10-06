#include "AppWindow.h"
#include <Windows.h>
#include "EngineTime.h"
#include "Vector3D.h"


AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	// Create Primitives
	/* Triangle Primitive Example
	vertex triangle_1_coords[] =
	{
		{-0.5f, -0.5f, 0.0f}, // POS 1
		{0.0f, 0.5f, 0.0f}, // POS 2
		{0.5f, -0.5f, 0.0f} // POS 3
	};
	triangle_1->InitializeTriangle(triangle_1_coords);
	*/

	/* Moving Quad 
	vertex quad_1_coords[] =
	{
		{Vector3D(-0.5f,-0.5f,0.0f),    Vector3D(-0.32f,-0.11f,0.0f),   Vector3D(0,0,0), Vector3D(0,1,0) }, // POS1 (bottom left)
		{Vector3D(-0.5f,0.5f,0.0f),     Vector3D(-0.11f,0.78f,0.0f),   Vector3D(1,1,0), Vector3D(0,1,1) }, // POS2 (top left)
		{ Vector3D(0.5f,-0.5f,0.0f),     Vector3D(0.75f,-0.73f,0.0f), Vector3D(0,0,1),  Vector3D(1,0,0) },// POS3 (bottom right)
		{ Vector3D(0.5f,0.5f,0.0f),     Vector3D(0.88f,0.77f,0.0f),    Vector3D(1,1,1), Vector3D(0,0,1) } // POS 4 (top right)
	};
	quad_1->InitializeQuad(quad_1_coords);
	quadList.push_back(quad_1);
	*/

	/*
	vertex rgb_quad_coords[] =
	{
		//X - Y - Z
		{-0.7f,-0.9f,0.0f,    -0.32f,-0.11f,0.0f,   0,0,0,  0,1,0 }, // POS1
		{-0.9f,0.1f,0.0f,     -0.11f,0.68f,0.0f,    1,1,0,  0,1,1 }, // POS2
		{ 0.9f,-0.4f,0.0f,     0.1f,-0.73f,0.0f,   0,0,1,  1,0,0 },// POS3
		{ -0.7f,-0.9f,0.0f,      0.8f,0.7f,1.0f,    1,1,1,  0,0,1 } // POS4
	};
	rgb_quad->InitializeQuad(rgb_quad_coords);
	quadList.push_back(rgb_quad);
	*/

	/*
	vertex quad_3_coords[] =
	{

		{0.2f, 0.2f, 0.0f}, // POS 1
		{0.2f, 0.8f, 0.0f}, // POS 2
		{0.8f, 0.2f, 0.0f}, // POS 3
		{0.8f, 0.8f, 0.0f} // POS 4
	};
	quad_3->InitializeQuad(quad_3_coords);
	*/

	vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
		{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) }

	};

	cube1->SetOrigin(Vector3D(0, 0, 0));
	cube1->SetScale(Vector3D(0.5, 0.5, 0.5));
	cube1->Initialize(vertex_list);

	cube2->SetOrigin(Vector3D(-0.9, 0.7, 0));
	cube2->SetScale(Vector3D(0.5, 0.5, 0.5));
	cube2->Initialize(vertex_list);

	cube3->SetOrigin(Vector3D(0.9, 0.7, 0));
	cube3->SetScale(Vector3D(0.5, 0.5, 0.5));
	cube3->Initialize(vertex_list);

	cube4->SetOrigin(Vector3D(0.9, -0.7, 0));
	cube4->SetScale(Vector3D(0.5, 0.5, 0.5));
	cube4->Initialize(vertex_list);

	cube5->SetOrigin(Vector3D(-0.9, -0.7, 0));
	cube5->SetScale(Vector3D(0.5, 0.5, 0.5));
	cube5->Initialize(vertex_list);

	/*
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertex_list);
	cout << "Array Size: " << size_list << endl;

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};


	m_ib = GraphicsEngine::get()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	m_ib->load(index_list, size_index_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(vertex_list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();


	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();


	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
	*/
}
 
void AppWindow::onUpdate()
{
	// Clear Render Target
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0, 0.3, 1);

	// Set Viewport
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	// Draw Primitives
	//triangle_1->DrawTriangle();
	//quad_1->UpdateQuadPosition(rc, m_delta_time);
	//rgb_quad->UpdateQuad();
	//quad_3->UpdateQuad();

	// For Cube
	cube1->SetAnimationSpeed(0.55);
	cube1->Update(m_delta_time, rc);
	cube1->Draw();

	cube2->SetAnimationSpeed(0.20);
	cube2->Update(m_delta_time, rc);
	cube2->Draw();

	cube3->SetAnimationSpeed(1.3);
	cube3->Update(m_delta_time, rc);
	cube3->Draw();

	cube4->SetAnimationSpeed(5.4);
	cube4->Update(m_delta_time, rc);
	cube4->Draw();

	cube5->SetAnimationSpeed(0.01);
	cube5->Update(m_delta_time, rc);
	cube5->Draw();

	m_swap_chain->present(true);

	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount();

	m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;
}


void AppWindow::onDestroy()
{
	Window::onDestroy();
	//triangle_1->GetVertexBuffer()->release();
	//quad_1->ReleaseBuffer();
	//rgb_quad->ReleaseBuffer();
	//quad_3->ReleaseBuffer();
	m_swap_chain->release();
	//quad_1->ReleaseShaders();
	//rgb_quad->ReleaseShaders();
	//quad_3->ReleaseShaders();

	// Release Cubes
	cube1->Release();
	cube2->Release();
	cube3->Release();
	cube4->Release();
	cube5->Release();
	GraphicsEngine::get()->release();
}

void AppWindow::UpdateQuadPosition(float m_delta_time)
{
	cc.m_time = ::GetTickCount();

	m_delta_pos += m_delta_time / 10.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;

	m_delta_scale += m_delta_time / 0.55f; // the lower the denominator, the faster the spin

	/* Lerp Implementation
	//cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(1.0f, 1.0f, 0), (sin(m_delta_scale) + 1.0f) / 2.0f));
	//temp.setTranslation(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f,1.5f, 0), m_delta_pos));
	//cc.m_world *= temp;
	*/
	// Scale -> Rotate -> Transform
	cc.m_world.setScale(Vector3D(0.2, 0.2, 0.2));

	temp.setIdentity();
	temp.setRotationZ(m_delta_scale);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_delta_scale);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(m_delta_scale);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setTranslation(Vector3D(1.0, 0, 0));
	cc.m_world *= temp;

	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH
	(
		(this->getClientWindowRect().right - this->getClientWindowRect().left) / 300.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 300.0f,
		-4.0f,
		4.0f
	);
	

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}

/*
Proper Order of Transformation:
https://gamedev.stackexchange.com/questions/16719/what-is-the-correct-order-to-multiply-scale-rotation-and-translation-matrices-f
 
*/

