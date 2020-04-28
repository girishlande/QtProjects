This project shows demo of direct vs queued connection. 
What are we doing in this project ? 

Creating new Worker class object (QObject)
We are creating new thread.
We are moving Worked object on this thread. 

On UI we have 2 push buttons to start and stop work. 
There is progressbar indicating progress of work. 

We are connecting push buttons to worker object methods to start and stop work.
First connection is queued and second is direct. 
Play around these connections to see the effect. 
connect(ui->pushButton,SIGNAL(clicked()),worker,SLOT(startWork()),Qt::QueuedConnection);
connect(ui->pushButton_2,SIGNAL(clicked()),worker,SLOT(stopWork()),Qt::DirectConnection);

Basically when we are calling direct connection between 2 different threads, it will directly call 
slot method. whereas if its queued connection then it will wait for the current slot execution to finish before calling
new slot method. 
