#pragma once

#include <string>

#include "ServiceResolver.hpp"

#include "..\Common\DeviceResources.h"
#include "ShaderStructures.h"
#include "..\Common\StepTimer.h"

struct b2Vec2;

namespace ChemistsFun
{
	class Debug2DScene;

	typedef Arcusical::ServiceModel::ServiceResolver<Debug2DScene> DebugDrawService;

	// This sample renderer instantiates a basic rendering pipeline.
	class Debug2DScene
	{
	public:
		Debug2DScene(const std::shared_ptr<DX::DeviceResources>& deviceResources);

		void MakeBrushes();
		void BlackBrush();
		void WhiteBrush();
		void BlueBrush();
		void RedBrush();
		void YellowBrush();
		void GreenBrush();

		void DrawCircle(float x, float y, float radius);
		void Debug2DScene::DrawText(std::wstring input, float box_left, float box_top, float box_right, float box_bottom);
		void DrawRectangle(float right, float left, float top, float bottom);
		void DrawPolygon(b2Vec2 *points, int sides);

		void Clear();

	private:
		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// Variables used with the rendering loop.
		bool	m_loadingComplete;
		float	height;
		float	width;
		float	aspectRatio;

		// Color brushes
		ID2D1SolidColorBrush *black;
		ID2D1SolidColorBrush *white;
		ID2D1SolidColorBrush *blue;
		ID2D1SolidColorBrush *red;
		ID2D1SolidColorBrush *yellow;
		ID2D1SolidColorBrush *green;
		ID2D1SolidColorBrush *activeBrush;
	};
}

