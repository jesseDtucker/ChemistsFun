#pragma once

#include "ServiceResolver.hpp"

#include "..\Common\DeviceResources.h"
#include "ShaderStructures.h"
#include "..\Common\StepTimer.h"

namespace ChemistsFun
{
	class Debug2DScene;

	typedef Arcusical::ServiceModel::ServiceResolver<Debug2DScene> DebugDrawService;

	// This sample renderer instantiates a basic rendering pipeline.
	class Debug2DScene
	{
	public:
		Debug2DScene(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void DrawCircle(float x, float y, float radius);

	private:
		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// Variables used with the rendering loop.
		bool	m_loadingComplete;
	};
}

