#pragma once

#include "Common\StepTimer.h"
#include "Common\DeviceResources.h"
#include "Content\Sample3DSceneRenderer.h"
#include "Content\SampleFpsTextRenderer.h"
#include "Content\Debug2DScene.h"

#include "Game.hpp"

// Renders Direct2D and 3D content on the screen.
namespace ChemistsFun
{
	class ChemistsFunMain : public DX::IDeviceNotify
	{
	public:
		ChemistsFunMain(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		~ChemistsFunMain();
		void CreateWindowSizeDependentResources();
		void StartRenderLoop();
		void StopRenderLoop();
		Concurrency::critical_section& GetCriticalSection() { return m_criticalSection; }

		PROP_GET(FluidGame::Game, Game);

		// IDeviceNotify
		virtual void OnDeviceLost();
		virtual void OnDeviceRestored();

		PROP_SET_AND_GET(bool, IsMovingLeft);
		PROP_SET_AND_GET(bool, IsMovingRight);

	private:
		void ProcessInput();
		void Update();
		bool Render();

		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// TODO: Replace with your own content renderers.
		std::unique_ptr<SampleFpsTextRenderer> m_fpsTextRenderer;
		std::unique_ptr<Debug2DScene> m_Debug2D;

		Windows::Foundation::IAsyncAction^ m_renderLoopWorker;
		Concurrency::critical_section m_criticalSection;

		// Rendering loop timer.
		DX::StepTimer m_timer;
	};
}