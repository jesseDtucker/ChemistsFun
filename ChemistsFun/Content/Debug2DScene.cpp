#include "pch.h"
#include "Debug2DScene.h"
#include "Box2D\Collision\Shapes\b2CircleShape.h"
#include "Box2D\Collision\Shapes\b2PolygonShape.h"
#include "Box2D\Collision\Shapes\b2EdgeShape.h"

#include "..\Common\DirectXHelper.h"

using namespace ChemistsFun;

using namespace DirectX;
using namespace Windows::Foundation;

// Loads vertex and pixel shaders from files and instantiates the cube geometry.
Debug2DScene::Debug2DScene(const std::shared_ptr<DX::DeviceResources>& deviceResources) :
	m_loadingComplete(false),
	m_deviceResources(deviceResources)
{
	auto context = m_deviceResources->GetD2DDeviceContext();

	MakeBrushes();
	activeBrush = black;

	width = (float) context->GetSize().width;
	height = (float) context->GetSize().height;

	aspectRatio = width / height;
}

void Debug2DScene::MakeBrushes()
{
	auto context = m_deviceResources->GetD2DDeviceContext();

	auto hr = context->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &black);
	hr = context->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &white);
	hr = context->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue), &blue);
	hr = context->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &red);
	hr = context->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &yellow);
	hr = context->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &green);
}

void Debug2DScene::BlackBrush()
{
	activeBrush = black;
}

void Debug2DScene::WhiteBrush()
{
	activeBrush = white;
}

void Debug2DScene::BlueBrush()
{
	activeBrush = blue;
}

void Debug2DScene::RedBrush()
{
	activeBrush = red;
}

void Debug2DScene::YellowBrush()
{
	activeBrush = yellow;
}

void Debug2DScene::GreenBrush()
{
	activeBrush = green;
}

void Debug2DScene::DrawCircle(float x, float y, float radius)
{
	auto context = m_deviceResources->GetD2DDeviceContext();

	width = (float)context->GetSize().width;
	height = (float)context->GetSize().height;

	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F((x / (SCREEN_HEIGHT / aspectRatio)) * width, (y / SCREEN_HEIGHT) * height), (radius / SCREEN_HEIGHT) * height, (radius / SCREEN_HEIGHT) * height);

	context->BeginDraw();
	context->DrawEllipse(ellipse, activeBrush);
	context->EndDraw();
}

void Debug2DScene::DrawText(std::wstring text, float box_left, float box_top, float box_right, float box_bottom)
{
	auto context = m_deviceResources->GetD2DDeviceContext();
	auto factory = m_deviceResources->GetDWriteFactory();

	width = (float)context->GetSize().width;
	height = (float)context->GetSize().height;

	D2D1_RECT_F textBox = D2D1::RectF((box_left / (SCREEN_HEIGHT / aspectRatio)) * width, (box_top / SCREEN_HEIGHT) * height, (box_right / (SCREEN_HEIGHT / aspectRatio)) * width, (box_bottom / SCREEN_HEIGHT) * height);
	IDWriteTextFormat *form;
	auto hr = factory->CreateTextFormat(L"Arial", NULL, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 16.0f, L"en-us", &form);

	context->BeginDraw();
	context->DrawText(text.c_str(), text.size(), form, textBox, activeBrush);
	context->EndDraw();
}

void Debug2DScene::DrawRectangle(float right, float left, float top, float bottom)
{
	auto context = m_deviceResources->GetD2DDeviceContext();

	width = (float)context->GetSize().width;
	height = (float)context->GetSize().height;

	D2D1_RECT_F rectangle = D2D1::RectF((left / (SCREEN_HEIGHT / aspectRatio)) * width, (top / SCREEN_HEIGHT) * height, (right / (SCREEN_HEIGHT / aspectRatio)) * width, (bottom / SCREEN_HEIGHT) * height);

	context->BeginDraw();
	context->DrawRectangle(rectangle, activeBrush);
	context->EndDraw();
}

void Debug2DScene::DrawPolygon(b2PolygonShape *polygon, int32 edges, b2Vec2 bodyPos)
{
	auto context = m_deviceResources->GetD2DDeviceContext();

	width = (float)context->GetSize().width;
	height = (float)context->GetSize().height;

	D2D1_POINT_2F point0 = { 0, 0 };
	D2D1_POINT_2F point1 = { 0, 0 };

	context->BeginDraw();

	for (int e(1); e <= edges; ++e)
	{
		point0.x = ((polygon->GetVertex(e - 1).x + bodyPos.x) / (SCREEN_HEIGHT / aspectRatio)) * width;
		point0.y = ((polygon->GetVertex(e - 1).y + bodyPos.y) / SCREEN_HEIGHT) * height;
		point1.x = ((polygon->GetVertex(e).x + bodyPos.x) / (SCREEN_HEIGHT / aspectRatio)) * width;
		point1.y = ((polygon->GetVertex(e).y + bodyPos.y) / SCREEN_HEIGHT) * height;

		context->DrawLine(point0, point1, activeBrush);
	}

	context->EndDraw();
}

void Debug2DScene::DrawEdge(b2EdgeShape *edge)
{
	auto context = m_deviceResources->GetD2DDeviceContext();

	width = (float)context->GetSize().width;
	height = (float)context->GetSize().height;

	D2D1_POINT_2F point0 = { 0, 0 };
	D2D1_POINT_2F point1 = { 0, 0 };

	context->BeginDraw();
	point0.x = (edge->m_vertex1.x / (SCREEN_HEIGHT / aspectRatio)) * width;
	point0.y = (edge->m_vertex1.y / SCREEN_HEIGHT) * height;
	point1.x = (edge->m_vertex2.x / (SCREEN_HEIGHT / aspectRatio)) * width;
	point1.y = (edge->m_vertex2.y / SCREEN_HEIGHT) * height;
	context->DrawLine(point0, point1, activeBrush);
	context->EndDraw();
}

void Debug2DScene::DrawBody(b2Body &body)
{
	auto fixture = body.GetFixtureList();

	while (fixture != nullptr)
	{
		auto shape = fixture->GetShape();

		switch (shape->GetType())
		{
		case(b2Shape::e_circle) : {
			auto drawTarget = dynamic_cast<b2CircleShape *>(shape);
			DrawCircle(drawTarget->GetPositionX() / (SCREEN_HEIGHT / aspectRatio), drawTarget->GetPositionY() / SCREEN_HEIGHT, drawTarget->m_radius / SCREEN_HEIGHT);
			break;
		}
		case(b2Shape::e_polygon) : {
			auto drawTarget = dynamic_cast<b2PolygonShape *>(shape);
			DrawPolygon(drawTarget, drawTarget->GetVertexCount(), body.GetPosition());
			break;
		}
		case(b2Shape::e_edge) : {
			auto drawTarget = dynamic_cast<b2EdgeShape *>(shape);
			DrawEdge(drawTarget);
			break;
		}
		default: ARC_ASSERT_MSG(false, "Bad Shape");
		}

		fixture = fixture->GetNext();
	}
}

void ChemistsFun::Debug2DScene::Clear()
{
	auto context = m_deviceResources->GetD2DDeviceContext();

	context->BeginDraw();
	context->Clear(D2D1::ColorF(D2D1::ColorF::White));
	context->EndDraw();
}
