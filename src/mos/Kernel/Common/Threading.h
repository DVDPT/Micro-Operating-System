#pragma once

class BaseUThread;
class BaseUScheduler;
class UTask;

typedef BaseUThread Thread;
typedef BaseUScheduler Scheduler;
typedef UTask Task;

#include "KernelConstants.h"
#include "KernelConfig.h"
#include "BaseUThread.h"
#include "UTask.h"
#include "BaseUScheduler.h"

#include "SystemTypes.h"
