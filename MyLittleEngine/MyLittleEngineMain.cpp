#include "pch.h"
#include "MyLittleEngineMain.h"
#include "Common\DirectXHelper.h"

#if _WINDOWS
#include "Common\WinPixGPUCapturererLoader.h"
#endif

using namespace MyLittleEngine;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
using namespace Concurrency;

// DirectX 12 ���ø����̼� ���ø��� ���� ������ https://go.microsoft.com/fwlink/?LinkID=613670&clcid=0x412�� ���� �ֽ��ϴ�.
// ���ø����̼��� �ε�Ǹ� ���ø����̼� �ڻ��� �ε��ϰ� �ʱ�ȭ�մϴ�.
MyLittleEngineMain::MyLittleEngineMain()
{
	// TODO: �⺻ ���� timestep ��� �ܿ� �ٸ� ������ �Ϸ��� Ÿ�̸� ������ �����մϴ�.
	// ��: 60FPS ���� timestep ������Ʈ ���� ��� ������ ȣ���մϴ�.
	/*
	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);
	*/
#if _WINDOWS
	LoadPIXGPUCapturer();
#endif
}

// �������� ����� �ʱ�ȭ�մϴ�.
void MyLittleEngineMain::CreateRenderers(const std::shared_ptr<DX::DeviceResources>& deviceResources)
{
	// TODO: �� �׸��� �� ������ �ʱ�ȭ�� ��ü�մϴ�.
	m_sceneRenderer = std::unique_ptr<Sample3DSceneRenderer>(new Sample3DSceneRenderer(deviceResources));

	OnWindowSizeChanged();
}

// �����Ӵ� �� �� ���ø����̼� ���¸� ������Ʈ�մϴ�.
void MyLittleEngineMain::Update()
{
	// ��� ��ü�� ������Ʈ�մϴ�.
	m_timer.Tick([&]()
	{
		// TODO: �� �׸��� �� ������ ������Ʈ �Լ��� ��ü�մϴ�.
		m_sceneRenderer->Update(m_timer);
	});
}

// ���� ���ø����̼� ���¿� ���� ���� �������� �������մϴ�.
// �������� �������Ǿ� ǥ���� �غ� �Ǹ� true�� ��ȯ�մϴ�.
bool MyLittleEngineMain::Render()
{
	// ó�� ������Ʈ�ϱ� ���� �ƹ��͵� ���������� ������.
	if (m_timer.GetFrameCount() == 0)
	{
		return false;
	}

	// ��� ��ü�� �������մϴ�.
	// TODO: �� �׸��� �� ������ ������ �Լ��� ��ü�մϴ�.
	return m_sceneRenderer->Render();
}

// â�� ũ�Ⱑ ���ϸ�(��: ����̽� ���� ����) ���ø����̼� ���¸� ������Ʈ�մϴ�.
void MyLittleEngineMain::OnWindowSizeChanged()
{
	// TODO: �� �׸��� �� �������� ũ�� ���� �ʱ�ȭ�� ��ü�մϴ�.
	m_sceneRenderer->CreateWindowSizeDependentResources();
}

// �Ͻ� �ߴ� ���°� �ƴ� ���� �˷� �ݴϴ�.
void MyLittleEngineMain::OnSuspending()
{
	// TODO: �̰��� ���� �Ͻ� �ߴ� ���� �ٲټ���.

	// �������� ���μ��� ���� ������ �Ͻ� ������ ���� ������ ���� �ֽ��ϴ�. ����
	// ���� �ߴܵ� ��ġ���� ���� �ٽ� ���۵� �� �ֵ��� ���� ��� ���¸� �����ϴ� ���� �����ϴ�. 

	m_sceneRenderer->SaveState();

	// ���ø����̼ǿ��� �ٽ� ����Ⱑ ���� ���� �޸� �Ҵ��� ����ϴ� ���,
	// �ش� �޸𸮸� �������Ͽ� �ٸ� ���ø����̼��� ����� �� �ֵ��� �غ�����.
}

// �� �̻� �Ͻ� �ߴ� ���°� �ƴ� ���� �˷� �ݴϴ�.
void MyLittleEngineMain::OnResuming()
{
	// TODO: �̰��� ���� �ٽ� ���� ���� �ٲټ���.
}

// �������� �ʿ��� ����̽� ���ҽ��� �������� �˸��ϴ�.
void MyLittleEngineMain::OnDeviceRemoved()
{
	// TODO: �ʿ��� ���ø����̼� �Ǵ� ������ ���¸� �����ϰ� �������� �������ϼ���.
	// �� �� �̻� ��ȿ���� ���� ���ҽ��Դϴ�.
	m_sceneRenderer->SaveState();
	m_sceneRenderer = nullptr;
}
