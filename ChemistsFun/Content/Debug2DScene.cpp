height
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

}

void Debug2DScene::DrawCircle(float x, float y, float radius)
{
	auto context = m_deviceResources->GetD2DDeviceContext();

	auto width = context->GetSize().width;
	auto height = context->GetSize().height;

	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius);
	ID2D1SolidColorBrush *black;
	auto hr = context->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &black);

	context->BeginDraw();
	context->DrawEllipse(ellipse, black);
	context->EndDraw();
}

void DrawText();

void Debug2DScene::DrawRectangle(float right, float left, float top, float bottom)
{
	auto context = m_deviceResources->GetD2DDeviceContext();

	D2D1_RECT_F rectangle = D2D1::RectF(left, top, right, bottom);
	ID2D1SolidColorBrush *black;
	auto hr = context->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &black);

	context->BeginDraw();
	context->DrawRectangle(rectangle, &black);
	context->EndDraw();
}

void ChemistsFun::Debug2DScene::Clear()
{
	auto context = m_deviceResources->GetD2DDeviceContext();
	context->BeginDraw();
	context->Clear(D2D1::ColorF(D2D1::ColorF::Pink));
	context->EndDraw();
}
