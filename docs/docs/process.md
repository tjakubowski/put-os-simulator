# Process

`Process` stores all important information about process in operation system.
The most important information about process can be printed using stream operator:
``` cpp
std::cout << *processss;
```

## State
- **Type:** `enum`
- **Details:** Indicate current process state.
- **Values:**
  - `New`
  - `Waiting`
  - `Ready`
  - `Running`

## name_
- **Type:** `std::string`
- **Details:** Stores process name.

## file_name_
- **Type:** `std::string`
- **Details:** Stores name of file containing process code.

## process_state_
- **Type:** `int`
- **Details:** Stores process state - `State`.

## id_
- **Type:** `int`
- **Details:** Stores the unique process id.

## priority_
- **Type:** `int`
- **Details:** Stores process priority.

## ax_
- **Type:** `int`
- **Details:** Stores AX register value.

## bx_
- **Type:** `int`
- **Details:** Stores BX register value.

## cx_
- **Type:** `int`
- **Details:** Stores CX register value.

## dx_
- **Type:** `int`
- **Details:** Stores DX register value.

## instruction_counter_
- **Type:** `int`
- **Details:** Holds the memory address of the next instruction that would be executed.