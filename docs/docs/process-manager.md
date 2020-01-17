# Process Manager

`ProccessManager` is a class that manages processes in the system - creating, killing and moving them between lists.

## last_process_id_
- **Type:** `static int`
- **Details:** Stores the last assigned process index. The value is incremented when creating a new process.

## processes_
- **Type:** `std::list<Process*>`
- **Details:** Stores pointers to all processes.

## new_processes_
- **Type:** `std::list<Process*>`
- **Details:** Stores pointers to all new processes.
- **Details:** Stores pointers to all processes.

## waiting_processes_
- **Type:** `std::list<Process*>`
- **Details:** Stores pointers to all waiting processes.

## ready_processes_
- **Type:** `std::list<Process*>`
- **Details:** Stores pointers to all ready processes.

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
  Creates new process with given name, name of file with process code and priority used in CPU scheduler and returns its pointer.

  ``` cpp
  ProcessManager::GetInstance().CreateProcess("helloworld", "hello_world.txt", 2);
  ```
  
## KillProcess()

- **Arguments:**
  - `{Process*} process | {int} process_id | {std::string} process_name`

- **Usage:**
  Kills the process and removes it from every list of processes.

  ``` cpp
  ProcessManager::GetInstance().KillProcess(process);
  ```
  ``` cpp
  ProcessManager::GetInstance().KillProcess("helloworld");
  ```
  ``` cpp
  ProcessManager::GetInstance().KillProcess(2);
  ```  
  
## GetProcess()

- **Arguments:**
  - `{int} process_id | {std::string} process_name`

- **Usage:**
  Returns pointer to the queried process

  ``` cpp
  auto found_process = ProcessManager::GetInstance().GetProcess("helloworld");
  ```
  ``` cpp
  auto found_process = ProcessManager::GetInstance().GetProcess(2);
  ```

## SetProcessNew()

- **Arguments:**
  - `{Process*} process | {int} process_id | {std::string} process_name`

- **Usage:**
  Sets process state to `State::New`.
  
  ``` cpp
  ProcessManager::GetInstance().SetProcessNew(process);
  ```
  ``` cpp
  ProcessManager::GetInstance().SetProcessNew("helloworld");
  ```
  ``` cpp
  ProcessManager::GetInstance().SetProcessNew(2);
  ```

## SetProcessWaiting()

- **Arguments:**
  - `{Process*} process | {int} process_id | {std::string} process_name`

- **Usage:**
  Sets process state to `State::Waiting` and sets `running_process` to it. Removes process from any other list of processes except `processes_`.
  
  ``` cpp
  ProcessManager::GetInstance().SetProcessWaiting(process);
  ```
  ``` cpp
  ProcessManager::GetInstance().SetProcessWaiting("helloworld");
  ```
  ``` cpp
  ProcessManager::GetInstance().SetProcessWaiting(2);
  ```
  
## SetProcessReady()

- **Arguments:**
  - `{Process*} process | {int} process_id | {std::string} process_name`

- **Usage:**
  Sets process state to `State::Ready` and sets `running_process` to it. Removes process from any other list of processes except `processes_`.

  ``` cpp
  ProcessManager::GetInstance().SetProcessReady(process);
  ```
  ``` cpp
  ProcessManager::GetInstance().SetProcessReady("helloworld");
  ```
  ``` cpp
  ProcessManager::GetInstance().SetProcessReady(2);
  ```
  
## SetProcessRunning()

- **Arguments:**
  - `{Process*} process | {int} process_id | {std::string} process_name`

- **Usage:**
  Sets process state to `State::Running` and sets `running_process` to it. Removes process from any other liss of processes except `processes_`.

  ``` cpp
  ProcessManager::GetInstance().SetProcessRunning(process);
  ```
  ``` cpp
  ProcessManager::GetInstance().SetProcessRunning("helloworld");
  ```
  ``` cpp
  ProcessManager::GetInstance().SetProcessRunning(2);
  ```

## PrintProcesses()

- **Arguments:**
  - `{std::vector<Process*>} processes (optional)`

- **Usage:**
  Prints out all processes or given list of processes
  
  ``` cpp
  ProcessManager::GetInstance().PrintProcesses();
  ```
  Prints out all processes or given list of processes
  
  ``` cpp
  ProcessManager::GetInstance().PrintProcesses(ProcessManager::GetInstance().ready_processes());
  ```
  
## PrintProcess()

- **Arguments:**
  - `{Process*} process | {int} process_id | {std::string} process_name`

- **Usage:**
  Prints out given `process` or found one by passing its `process_id` or `process_name`.
  
  ``` cpp
  ProcessManager::GetInstance().PrintProcess(process);
  ```
  ``` cpp
  ProcessManager::GetInstance().PrintProcess("helloworld");
  ```
  ``` cpp
  ProcessManager::GetInstance().PrintProcess(2);
  ```