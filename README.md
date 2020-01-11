# Documentation

1. [Process](#process)
    - [State](#state)
    - [name_](#name_)
    - [file_name_](#file_name_)
    - [process_state_](#process_state_)
    - [id_](#id_)
    - [priority_](#priority_)
    - [ax_](#ax_)
    - [bx_](#bx_)
    - [cx_](#cx_)
    - [dx_](#dx_)
    - [instruction_counter_](#instruction_counter_)
2. [Process Manager](#process-manager)
    - [last_process_id_](#last_process_id_)
    - [processes_](#processes_)
    - [ready_processes_](#ready_processes_)
    - [waiting_processes_](#waiting_processes_)
    - [running_process_](#running_process_)
    - [dummy_process_](#dummy_process_)
    - [KillProcess()](#killprocess)
    - [GetProcess()](#getprocess)
    - [SetProcessRunning()](#setprocessrunning)
    - [SetProcessReady()](#setprocessready)
    - [SetProcessWaiting()](#setprocesswaiting)
    - [PrintAllProcesses()](#printallprocesses)
    - [PrintWaitingProcesses()](#printwaitingprocesses)
    - [PrintReadyProcesses()](#printreadyprocesses)
    - [PrintRunningProcess()](#printrunningprocess)
    - [PrintProcesses()](#printprocesses)
    - [PrintProcess()](#printprocess)

## Process

`Process` stores all important information about process in operation system.
The most important information about process can be printed using stream operator:
``` cpp
std::cout << *process;
```

### State
- **Type:** `enum`
- **Details:** Indicate current process state.
- **Values:**
  - `New`
  - `Waiting`
  - `Ready`
  - `Running`

### name_
- **Type:** `std::string`
- **Details:** Stores process name.

### file_name_
- **Type:** `std::string`
- **Details:** Stores name of file containing process code.

### process_state_
- **Type:** `int`
- **Details:** Stores process state - `State`.

### id_
- **Type:** `int`
- **Details:** Stores the unique process id.

### priority_
- **Type:** `int`
- **Details:** Stores process priority.

### ax_
- **Type:** `int`
- **Details:** Stores AX register value.

### bx_
- **Type:** `int`
- **Details:** Stores BX register value.

### cx_
- **Type:** `int`
- **Details:** Stores CX register value.

### dx_
- **Type:** `int`
- **Details:** Stores DX register value.

### instruction_counter_
- **Type:** `int`
- **Details:** Holds the memory address of the next instruction that would be executed.

## Process Manager

`ProccessManager` is a class that manages processes in the system - creating, killing and moving them between lists.

### last_process_id_
- **Type:** `static int`
- **Details:** Stores the last assigned process index. The value is incremented when creating a new process.

### processes_
- **Type:** `std::list<Process*>`
- **Details:** Stores pointers to all processes except dummy one.

### ready_processes_
- **Type:** `std::list<Process*>`
- **Details:** Stores pointers to all ready processes.

### waiting_processes_
- **Type:** `std::list<Process*>`
- **Details:** Stores pointers to all waiting processes.

### running_process_
- **Type:** `Process*`
- **Details:** Stores a pointer to the currently running process.

### dummy_process_
- **Type:** `Process*`
- **Details:** A dummy process created on operation system startup. This process is run when there is no ready process.

### CreateProcess()

- **Arguments:**
  - `{std::string} process_name`
  - `{std::string} process_file`
  - `{int} priority`

- **Usage:**
  Creates new process with given name, name of file with process code and priority used in CPU scheduler.

  ``` cpp
  process_manager.CreateProcess("helloworld", "hello_world.txt", 2);
  ```
  
### KillProcess()

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
  
### GetProcess()

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
  
### SetProcessRunning()

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
  
### SetProcessReady()

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

### SetProcessWaiting()

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

### PrintAllProcesses()

- **Usage:**
  Prints out processes from `processes_` list.
  
  ``` cpp
  process_manager.PrintAllProcesses();
  ```

### PrintWaitingProcesses()

- **Usage:**
  Prints out processes from `waiting_processes_` list.
  
  ``` cpp
  process_manager.PrintWaitingProcesses();
  ```

### PrintReadyProcesses()

- **Usage:**
  Prints out processes from `ready_processes_` list.
  
  ``` cpp
  process_manager.PrintReadyProcesses();
  ```

### PrintRunningProcess()

- **Usage:**
  Prints out currently running process `running_process_`.
  
  ``` cpp
  process_manager.PrintRunningProcess();
  ```
  
### PrintProcesses()

- **Usage:**
  Prints out all lists of processes and `running_process_`.
  
  ``` cpp
  process_manager.PrintProcesses();
  ```
  
### PrintProcess()

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

# Responsibilities

| Module                           | User             |
| -------------------------------- | ---------------- |
| CPU scheduling (priority method) | @ggEx86          |
| Process management               | @tjakubowski     |
| Virtual memory management        | @kamilmosek      |
| RAM management                   | @ruscin          |
| Process synchronization          | @PrzerostNadSens |
| FAT - file management            | -                |
| Assembler interpreter            | @molejnik1998    |
| Windows-based interface          | @Vidugavia       |
