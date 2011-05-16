#include "KernelController.h"

KernelController::KernelController()
	: _idleThread((ThreadFunction)IdleThreadRoutine,NULL)
{
	_idleThread.Start();
}

Void KernelController::IdleThreadRoutine()
{
	while (true)
	{

	}
}

