#include "pch.h"
#include "ChemistsFunMain.h"
#include "Common\DirectXHelper.h"

using namespace std;
using namespace ChemistsFun;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
using namespace Concurrency;

// Loads and initializes application assets when the application is loaded.
ChemistsFunMain::ChemistsFunMain(const std::shared_ptr<DX::DeviceResources>& deviceResources) :
	m_deviceResources(deviceResources), m_pointerLocationX(0.0f)
{
	// Register to be notified if the Device is lost or recreated
	m_deviceResources->RegisterDeviceNotify(this);

	m_Debug2D = make_unique<Debug2DScene>(m_deviceResources);
}

ChemistsFunMain::~ChemistsFunMain()
{
	// Deregister device notification
	m_deviceResources->RegisterDeviceNotify(nullptr);
}

// Updates application state when the window size changes (e.g. device orientation change)
void ChemistsFunMain::CreateWindowSizeDependentResources() 
{
	// TODO: Replace this with the size-dependent initialization of your app's content.
}

void ChemistsFunMain::StartRenderLoop()
{
	// If the animation render loop is already running then do not start another thread.
	if (m_renderLoopWorker != nullptr && m_renderLoopWorker->Status == AsyncStatus::Started)
	{
		return;
	}

	// Create a task that will be run on a background thread.
	auto workItemHandler = ref new WorkItemHandler([this](IAsyncAction ^ action)
	{
		// Calculate the updated frame and render once per vertical blanking interval.
		while (action->Status == AsyncStatus::Started)
		{
			critical_section::scoped_lock lock(m_criticalSection);
			Update();
			if (Render())
			{
				m_deviceResources->Present();
			}
		}
	});

	m_game.RunSim();

	// Run task on a dedicated high priority background thread.
	m_renderLoopWorker = ThreadPool::RunAsync(workItemHandler, WorkItemPriority::High, WorkItemOptions::TimeSliced);
}

void ChemistsFunMain::StopRenderLoop()
{
	m_renderLoopWorker->Cancel();
}

// Updates the application state once per frame.
void ChemistsFunMain::Update() 
{
	ProcessInput();
	Render();
}

// Process all input from the user before updating game state
void ChemistsFunMain::ProcessInput()
{
	// TODO: Add per frame input handling here.
}

b2Vec2 TransformToLocal(const b2Vec2& vec)
{
	return {vec.x * 10, vec.y * 10};
}

// Renders the current frame according to the current application state.
// Returns true if the frame was rendered and is ready to be displayed.
bool ChemistsFunMain::Render() 
{
	auto context = m_deviceResources->GetD2DDeviceContext();

	// Render the scene objects.
	// TODO: Replace this with your app's content rendering functions.
	m_Debug2D->Clear();
	m_Debug2D->DrawCircle(20.5f, 50.5f, 50.1f);

	auto particles = m_game.GetParticlesPositions();
	for (int i = 0; i < particles.first; ++i)
	{
		auto particlePos = particles.second[i];
		auto screenSpaceVec = TransformToLocal(particlePos);
		m_Debug2D->DrawCircle(screenSpaceVec.x, screenSpaceVec.y, 5.0f);
	}

	m_Debug2D->DrawText(L"MY TEXT", 100.0f, 100.0f, 150.0f, 50.0f);

	return true;
}

// Notifies renderers that device resources need to be released.
void ChemistsFunMain::OnDeviceLost()
{
	m_fpsTextRenderer->ReleaseDeviceDependentResources();
}

// Notifies renderers that device resources may now be recreated.
void ChemistsFunMain::OnDeviceRestored()
{
	m_fpsTextRenderer->CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}
