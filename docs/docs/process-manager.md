# Process Manager

`ProccessManager` is a class that manages processes in the system - creating, killing and moving them between lists.

## last_process_id_
- **Type:** `static int`
- **Details:** Stores the last assigned process index. The value is incremented when creating a new process.

## processes_
- **Type:** `std::list<Process*>`
- **Details:** Stores pointers to all processes except dummy one.

## ready_processes_
- **Type:** `std::list<Process*>`
- **Details:** Stores pointers to all ready processes.

## waiting_processes_
- **Type:** `std::list<Process*>`
- **Details:** Stores pointers to all waiting processes.

## running_process_
- **Type:** `Process*`
- **Details:** Stores a pointer to the currently running process.

## dummy_process_
- **Type:** `Process*`
- **Details:** A dummy process created on operation system startup. This process is run when there is no ready process.

## CreateProcess()

- **Arguments:**
  - `{std::string} process_name`
  - `{std::string} process_file`
  - `{int} priority`

- **Usage:**
  Creates new process with given name, name of file with process code and priority used in CPU scheduler.

  ``` cpp
  process_manager.CreateProcess("helloworld", "hello_world.txt", 2);
  ```
  
## KillProcess()

- **Arguments:**
  - `{Process*} process | {int} process_id | {std::string} process_name`

- **Usage:**
  Kills the process and removes it from every list of processes.

  ``` cpp
  process_manager.KillProcess(process);
  ```
  ``` cpp
  process_manager.KillProcess("helloworld");
  ```
  ``` cpp
  process_manager.KillProcess(2);
  ```  
  
## GetProcess()

- **Arguments:**
  - `{int} process_id | {std::string} process_name`

- **Usage:**
  Returns pointer to the queried process

  ``` cpp
  auto found_process = process_manager.GetProcess("helloworld");
  ```
  ``` cpp
  auto found_process = process_manager.GetProcess(2);
  ```
  
## SetProcessRunning()

- **Arguments:**
  - `{Process*} process | {int} process_id | {std::string} process_name`

- **Usage:**
  Sets process state to `State::Running` and sets `running_process` to it. Removes process from any other liss of processes except `processes_`.

  ``` cpp
  process_manager.SetProcessRunning(process);
  ```
  ``` cpp
  process_manager.SetProcessRunning("helloworld");
  ```
  ``` cpp
  process_manager.SetProcessRunning(2);
  ```
  
## SetProcessReady()

- **Arguments:**
  - `{Process*} process | {int} process_id | {std::string} process_name`

- **Usage:**
  Sets process state to `State::Ready` and sets `running_process` to it. Removes process from any other list of processes except `processes_`.

  ``` cpp
  process_manager.SetProcessReady(process);
  ```
  ``` cpp
  process_manager.SetProcessReady("helloworld");
  ```
  ``` cpp
  process_manager.SetProcessReady(2);
  ```

## SetProcessWaiting()

- **Arguments:**
  - `{Process*} process | {int} process_id | {std::string} process_name`

- **Usage:**
  Sets process state to `State::Waiting` and sets `running_process` to it. Removes process from any other list of processes except `processes_`.
  
  ``` cpp
  process_manager.SetProcessWaiting(process);
  ```
  ``` cpp
  process_manager.SetProcessWaiting("helloworld");
  ```
  ``` cpp
  process_manager.SetProcessWaiting(2);
  ```

## PrintAllProcesses()

- **Usage:**
  Prints out processes from `processes_` list.
  
  ``` cpp
  process_manager.PrintAllProcesses();
  ```

## PrintWaitingProcesses()

- **Usage:**
  Prints out processes from `waiting_processes_` list.
  
  ``` cpp
  process_manager.PrintWaitingProcesses();
  ```

## PrintReadyProcesses()

- **Usage:**
  Prints out processes from `ready_processes_` list.
  
  ``` cpp
  process_manager.PrintReadyProcesses();
  ```

## PrintRunningProcess()

- **Usage:**
  Prints out currently running process `running_process_`.
  
  ``` cpp
  process_manager.PrintRunningProcess();
  ```
  
## PrintProcesses()

- **Usage:**
  Prints out all lists of processes and `running_process_`.
  
  ``` cpp
  process_manager.PrintProcesses();
  ```
  
## PrintProcess()

- **Arguments:**
  - `{Process*} process | {int} process_id | {std::string} process_name`

- **Usage:**
  Prints out given `process` or found one by passing its `process_id` or `process_name`.
  
  ``` cpp
  process_manager.PrintProcess(process);
  ```
  ``` cpp
  process_manager.PrintProcess("helloworld");
  ```
  ``` cpp
  process_manager.PrintProcess(2);
  ```