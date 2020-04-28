#include "task.h"
#include <windows.h>

Task::Task()
{

}

void Task::run()
{

    for(int i=1;i<=100;i++) {
        Sleep(100);
        emit updateProgress(i);
    }

}
