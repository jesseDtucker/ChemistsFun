#include "pch.h"
#include "Debug2DScene.h"

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

	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(x * width, y * height), radius * aspectRatio, radius);

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

	D2D1_RECT_F textBox = D2D1::RectF(box_left * width, box_top * height, box_right * width, box_bottom * height);
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

	D2D1_RECT_F rectangle = D2D1::RectF(left * width, top * height, right * width, bottom * height);

	context->BeginDraw();
	context->DrawRectangle(rectangle, activeBrush);
	context->EndDraw();
}

void ChemistsFun::Debug2DScene::Clear()
{
	auto context = m_deviceResources->GetD2DDeviceContext();

	context->BeginDraw();
	context->Clear(D2D1::ColorF(D2D1::ColorF::White));
	context->EndDraw();
}
