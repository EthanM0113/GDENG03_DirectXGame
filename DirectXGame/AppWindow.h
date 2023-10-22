#pragma once
#include <vector>

#include "Cube.h"
#include "imgui.h"
#include "InputListener.h"
#include "Window.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "Matrix4x4.h"
#include  "PixelShader.h"
#include "VertexShader.h"

class AppWindow : public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow();

	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Point& deltaPos);

	virtual void onLeftMouseDown(const Point& deltaPos);
	virtual void onLeftMouseUp(const Point& deltaPos);

	virtual void onRightMouseDown(const Point& deltaPos);
	virtual void onRightMouseUp(const Point& deltaPos);

	void updateCamera();
private:
	std::vector<Cube*> cubeList;

	float ticks = 0.0f;

	SwapChain* m_swap_chain;
	VertexBuffer* m_vertex_buffer;
	ConstantBuffer* m_constant_buffer;
	IndexBuffer* m_index_buffer;

	VertexShader* m_vertex_shader;
	PixelShader* m_pixel_shader;

private:
	long m_old_delta;
	long m_new_delta;
	float m_delta_time;

	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	float m_scale_cube = 1;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;
	Matrix4x4 m_world_cam;

	AGameObject::CBData cc;
	Matrix4x4 world_cam;
	Matrix4x4 temp;

// GUI Variables
private:
	bool show_demo_window = false;
	ImVec4 clear_color = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
	const char* animationButtonLabel = "Pause Animation";
	bool isAnimationPaused = false;
	bool isClearColorBeingEdited = false;

};