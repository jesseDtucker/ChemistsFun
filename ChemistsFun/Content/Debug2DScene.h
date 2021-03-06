#pragma once

#include <string>

#include "ServiceResolver.hpp"

#include "..\Common\DeviceResources.h"
#include "ShaderStructures.h"
#include "..\Common\StepTimer.h"

struct b2Vec2;
class b2Body;
class b2PolygonShape;
class b2EdgeShape;

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
		void BlueBrush2();
		void BlueBrush3();
		void BlueBrush4();
		void RedBrush();
		void YellowBrush();
		void GreenBrush();

		void DrawCircle(float x, float y, float radius);
		void DrawText(std::wstring input, float box_left, float box_top, float box_right, float box_bottom);
		void DrawRectangle(float right, float left, float top, float bottom);
		void DrawPolygon(b2PolygonShape *polygon, int32 edges, b2Vec2 bodyPos);
		void DrawEdge(b2EdgeShape *edge);
		void DrawBody(b2Body& body);

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
		ID2D1SolidColorBrush *blue2;
		ID2D1SolidColorBrush *blue3;
		ID2D1SolidColorBrush *blue4;
		ID2D1SolidColorBrush *red;
		ID2D1SolidColorBrush *yellow;
		ID2D1SolidColorBrush *green;
		ID2D1SolidColorBrush *activeBrush;
	};
}

