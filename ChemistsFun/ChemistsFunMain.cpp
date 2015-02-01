#include "pch.h"
#include "ChemistsFunMain.h"
#include "Common\DirectXHelper.h"

#include "B2_Helper.hpp"
#include "LevelEntries.hpp"

using namespace std;
using namespace ChemistsFun;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
using namespace Concurrency;
using namespace FluidGame;

// Loads and initializes application assets when the application is loaded.
ChemistsFunMain::ChemistsFunMain(const std::shared_ptr<DX::DeviceResources>& deviceResources) 
	: m_deviceResources(deviceResources)
	, m_IsMovingLeft(false)
	, m_IsMovingRight(false)
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

	if (!m_Game.GetIsRunning())
	{
		m_Game.RunSim(FluidGame::LevelEntries::LoadLevelTwo(PARTICLE_RADIUS));
	}

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
	return vec;
}

b2AABB GenerateBoundingBox(b2Body& body)
{
	b2AABB result;
	result.lowerBound = { FLT_MAX, FLT_MAX };
	result.upperBound = { -FLT_MAX, -FLT_MAX };
	auto fixture = body.GetFixtureList();
	while (fixture != nullptr)
	{
		result.Combine(result, fixture->GetAABB(0));
		fixture = fixture->GetNext();
	}

	return result;
}

void DrawParticles(b2ParticleSystem* particleSystem, Debug2DScene& debugScene)
{
	debugScene.BlueBrush();
	auto particlePositions = particleSystem->GetPositionBuffer();
	auto particleCount = particleSystem->GetParticleCount();
	for (int i = 0; i < particleCount; ++i)
	{
		auto particlePos = particlePositions[i];
		auto screenSpaceVec = TransformToLocal(particlePos);

		debugScene.DrawCircle(screenSpaceVec.x, screenSpaceVec.y, PARTICLE_RADIUS);
	}
}

void DrawBodies(WorldPtr world, Debug2DScene& debugScene)
{
	debugScene.BlackBrush();
	auto body = world->GetBodyList();
	while (body != nullptr)
	{
		debugScene.DrawBody(*body);
		body = body->GetNext();
	}
}

void DrawKillBoxes(Level& level, Debug2DScene& debugScene)
{
	debugScene.GreenBrush();
	for (auto& box : level.GetKillBoxes())
	{
		b2AABB aabb;
		box.second.ComputeAABB(&aabb, box.first, 0);
		auto left = aabb.lowerBound.x;
		auto right = aabb.upperBound.x;
		auto top = aabb.lowerBound.y;
		auto bottom = aabb.upperBound.y;
		debugScene.DrawRectangle(right, left, top, bottom);
	}
}

void DrawCharacter(Character& character, Debug2DScene& debugScene)
{
	auto body = character.GetBody();
	debugScene.RedBrush();
	debugScene.DrawBody(*body);
}

// Renders the current frame according to the current application state.
// Returns true if the frame was rendered and is ready to be displayed.
bool ChemistsFunMain::Render() 
{
	auto context = m_deviceResources->GetD2DDeviceContext();

	// Render the scene objects.
	// TODO: Replace this with your app's content rendering functions.
	m_Debug2D->Clear();

	context->BeginDraw();
	m_Debug2D->BlueBrush();
	DrawParticles(m_Game.GetCurrentLevel()->GetParticleSystem(), *m_Debug2D);
	m_Debug2D->GreenBrush();
	DrawBodies(m_Game.GetCurrentLevel()->GetWorld(), *m_Debug2D);
	//DrawKillBoxes(*m_Game.GetCurrentLevel(), *m_Debug2D);
	DrawCharacter(*m_Game.GetCurrentLevel()->GetMainCharacter(), *m_Debug2D);

	context->EndDraw();

	if (m_IsMovingLeft && !m_IsMovingRight)
	{
		m_Game.GetCurrentLevel()->GetMainCharacter()->MoveLeft();
	}
	if (m_IsMovingRight && !m_IsMovingLeft)
	{
		m_Game.GetCurrentLevel()->GetMainCharacter()->MoveRight();
	}

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
