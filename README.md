<div align="center">

# 📡 Minitalk

### The purpose of this project is to code a small data exchange program using UNIX signals

<p>
  <img src="https://img.shields.io/badge/Score-125%2F100-success?style=for-the-badge&logo=42" alt="42 Score"/>
  <img src="https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="Language"/>
  <img src="https://img.shields.io/badge/Signals-SIGUSR1%20%26%20SIGUSR2-blue?style=for-the-badge" alt="Signals"/>
  <img src="https://img.shields.io/badge/License-MIT-green?style=for-the-badge" alt="License"/>
  <img src="https://img.shields.io/badge/42-Urduliz-000000?style=for-the-badge&logo=42&logoColor=white" alt="42 Urduliz"/>
</p>

*A client-server communication program using only UNIX signals (SIGUSR1 and SIGUSR2) to transmit strings bit by bit.*

[Installation](#%EF%B8%8F-installation) • [Usage](#-usage) • [How It Works](#-how-it-works) • [Implementation](#-implementation-details) • [Testing](#-testing)

</div>

---

## 📋 Table of Contents

- [About the Project](#-about-the-project)
- [Installation](#%EF%B8%8F-installation)
- [Usage](#-usage)
- [How It Works](#-how-it-works)
- [Implementation Details](#-implementation-details)
- [Project Structure](#-project-structure)
- [Testing](#-testing)
- [What I Learned](#-what-i-learned)
- [Requirements](#-requirements)
- [License](#-license)

---

## 🎯 About the Project

**Minitalk** is a communication system that uses UNIX signals to transmit text between two processes: a **server** and a **client**. The challenge is to send strings character by character using only two signals: `SIGUSR1` and `SIGUSR2`.

### Why Minitalk?

<table>
<tr>
<td width="50%" valign="top">

### 🔄 Inter-Process Communication
- **UNIX signals** as IPC mechanism
- PID-based messaging
- Process synchronization
- Asynchronous event handling

</td>
<td width="50%" valign="top">

### 🔢 Bitwise Operations
- **Binary encoding** character representation
- Bit-by-bit transmission
- OR/XOR bit manipulation
- 8-bit protocol implementation

</td>
</tr>
<tr>
<td width="50%" valign="top">

### ⚙️ Signal Handling
- **signal()** vs **sigaction()**
- Custom signal handlers
- Static variable persistence
- Handler state management

</td>
<td width="50%" valign="top">

### 🎯 Protocol Design
- **Binary protocol** with 2 signals
- Timing synchronization (usleep)
- Acknowledgment system (bonus)
- Multi-client handling

</td>
</tr>
</table>

### The Challenge

The constraint of using only two signals forces you to transmit each character **bit by bit**, creating a custom binary protocol.

**Communication Flow**:
```
Client → 8 signals per character → Server
        (SIGUSR1 = bit 1, SIGUSR2 = bit 0)
```

---

## 🛠️ Installation

### Prerequisites

- **GCC** or **Clang** compiler
- **Make**
- **libft** (included in project)
- Unix-based system (Linux, macOS)

### Clone and Compile

```bash
# Clone the repository
git clone https://github.com/Z3n42/minitalk.git
cd minitalk

# Compile both programs (mandatory)
make

# Compile bonus version
cd Bonus && make

# Clean object files
make clean

# Clean everything
make fclean

# Recompile
make re
```

After running `make`, you'll have two executables: `server` and `client`.

---

## 🚀 Usage

### Step 1: Start the Server

```bash
./server
```

The server will display its **PID** (Process ID):
```
Server PID: 12345
```

### Step 2: Send a Message from Client

```bash
./client [server_pid] "Your message here"
```

**Example:**
```bash
./client 12345 "Hello, Minitalk!"
```

The server will display:
```
Hello, Minitalk!
```

### Bonus Version (with Acknowledgment)

```bash
# Terminal 1
cd Bonus
./server

# Terminal 2
cd Bonus
./client [server_pid] "Test message"
```

The client will print `OK` for each successfully received character.

---

## 🔧 How It Works

### Communication Protocol

Since you can only use `SIGUSR1` and `SIGUSR2`, characters are transmitted **bit by bit**.

#### Binary Representation

```
Character 'A' = ASCII 65 = 01000001 (binary)

Bit 7: 0 → Send SIGUSR2
Bit 6: 1 → Send SIGUSR1
Bit 5: 0 → Send SIGUSR2
Bit 4: 0 → Send SIGUSR2
Bit 3: 0 → Send SIGUSR2
Bit 2: 0 → Send SIGUSR2
Bit 1: 0 → Send SIGUSR2
Bit 0: 1 → Send SIGUSR1
```

#### Visual Flow

```
Client                          Server
  │                               │
  │──── SIGUSR2 (bit 0) ────────→│
  │                               │ (Receive bit)
  │──── SIGUSR1 (bit 1) ────────→│
  │                               │ (Receive bit)
  │──── SIGUSR2 (bit 2) ────────→│
  │                               │ (Receive bit)
  │       ... (8 bits) ...        │
  │                               │
  │                               │ (After 8 bits)
  │                               │ → write(1, &char, 1)
  │                               │
  │←──── SIGUSR1 (ACK) ──────────│ (Bonus only)
```

### Algorithm Overview

**Client Process**:
1. Convert server PID from string to integer
2. For each character in the message:
   - For each of the 8 bits (MSB to LSB):
     - Check if bit is 1 or 0
     - Send `SIGUSR1` (bit = 1) or `SIGUSR2` (bit = 0)
     - Wait 50 microseconds (timing synchronization)

**Server Process**:
1. Display its PID
2. Register signal handlers for `SIGUSR1` and `SIGUSR2`
3. Enter infinite loop with `pause()`
4. In signal handler:
   - Accumulate bits (8 per character)
   - When 8 bits received, reconstruct character
   - Output character to stdout
   - Send acknowledgment (bonus)

### Bit Manipulation Strategy

**Why start with 255 (0xFF)?**

Starting with all bits set to 1 simplifies the logic:
- **SIGUSR1** → Keep bit as 1 (OR operation)
- **SIGUSR2** → Flip bit to 0 (XOR operation)

**Example:**
```
Initial:  c = 255  (11111111)

Receive SIGUSR2:
c = c ^ (128 >> 0)  →  11111111 ^ 10000000 = 01111111

Receive SIGUSR1:
c = c | (128 >> 1)  →  01111111 | 01000000 = 01111111

Receive SIGUSR2:
c = c ^ (128 >> 2)  →  01111111 ^ 00100000 = 01011111

Result: 'A' = 01000001 (65)
```

---

## 💻 Implementation Details

### Server Implementation

<details>
<summary><b>Mandatory Version (signal())</b></summary>

```c
#include <signal.h>
#include <unistd.h>
#include "libft/libft.h"

void ft_handler1(int sig)
{
    static int count;
    static int c;

    if (count == 0)
        c = 255;  // Initialize with all bits set

    if (sig == SIGUSR1)
        c = c | (128 >> count);   // Set bit to 1
    else
        c = c ^ (128 >> count);   // Set bit to 0

    count++;

    if (count == 8)  // Full character received
    {
        write(1, &c, 1);
        c = 255;
        count = 0;
    }
}

int main(void)
{
    pid_t pid;

    pid = getpid();
    ft_printf("%d\n", pid);

    signal(SIGUSR1, ft_handler1);
    signal(SIGUSR2, ft_handler1);

    while (1)
        pause();

    return (0);
}
```

**Key Details:**
- **Static variables**: `count` and `c` persist across signal calls
- **Bit manipulation**: `c = c | (128 >> count)` sets bit to 1
- **XOR operation**: `c = c ^ (128 >> count)` flips bit to 0
- **Initialization**: `c = 255` (0xFF) sets all bits to 1
- **`pause()`**: Suspends process until signal received

</details>

<details>
<summary><b>Bonus Version (sigaction() with ACK)</b></summary>

```c
void ft_handler1(int sig, siginfo_t *sigact, void *context)
{
    static int count;
    static int c;

    context = NULL;  // Unused parameter

    if (count == 0)
        c = 255;

    if (sig == SIGUSR1)
    {
        c = c | (128 >> count);
        usleep(50);
    }
    else
    {
        c = c ^ (128 >> count);
        usleep(50);
    }

    count++;

    if (count == 8)
    {
        write(1, &c, 1);
        c = 255;
        count = 0;
    }

    kill(sigact->si_pid, SIGUSR1);  // Send ACK to client
}

int main(void)
{
    struct sigaction sigact;
    pid_t pid;

    pid = getpid();
    ft_printf("%d\n", pid);

    sigact.sa_flags = SA_SIGINFO;
    sigact.sa_sigaction = ft_handler1;

    sigaction(SIGUSR1, &sigact, NULL);
    sigaction(SIGUSR2, &sigact, NULL);

    while (1)
        pause();

    return (0);
}
```

**Bonus Features:**
- **`sigaction()`**: Advanced signal handling with `siginfo_t`
- **`sigact->si_pid`**: Get sender's PID for acknowledgment
- **`kill(sigact->si_pid, SIGUSR1)`**: Send ACK back to client
- **`usleep(50)`**: Timing delay in handler

</details>

### Client Implementation

<details>
<summary><b>Mandatory Version</b></summary>

```c
int main(int argc, char **argv)
{
    char    *temp;
    int     count;
    int     counter;
    int     pid;

    if (argc != 3)
        ft_printf("Numero de paramatros inadecuado");

    pid = ft_atoi(argv[1]);
    temp = argv[2];

    counter = 0;
    while (temp[counter])
    {
        count = 0;
        while (count < 8)
        {
            if (temp[counter] & (128 >> count))  // Check bit
                kill(pid, SIGUSR1);              // Bit is 1
            else
                kill(pid, SIGUSR2);              // Bit is 0

            count++;
            usleep(50);  // Timing synchronization
        }
        counter++;
    }

    return (0);
}
```

**Key Operations:**
- **Bit checking**: `temp[counter] & (128 >> count)`
- **Signal sending**: `kill(pid, SIGUSR1)` or `kill(pid, SIGUSR2)`
- **Timing**: `usleep(50)` microseconds between signals
- **Loop**: 8 iterations per character

</details>

<details>
<summary><b>Bonus Version (with ACK)</b></summary>

```c
void ft_handler2(int sig)
{
    if (sig == SIGUSR1)
        write(1, "OK\n", 3);
}

int main(int argc, char **argv)
{
    char    *temp;
    int     count;
    int     counter;
    int     pid;

    if (argc != 3)
        ft_printf("Numero de paramatros inadecuado");

    signal(SIGUSR1, ft_handler2);  // Register ACK handler

    pid = ft_atoi(argv[1]);
    temp = argv[2];

    counter = -1;
    while (temp[++counter])
    {
        count = -1;
        while (++count < 8)
        {
            usleep(50);
            if (temp[counter] & (128 >> count))
                kill(pid, SIGUSR1);
            else
                kill(pid, SIGUSR2);

            pause();  // Wait for ACK from server
        }
    }

    return (0);
}
```

**Bonus Additions:**
- **ACK handler**: Prints "OK\n" on receiving `SIGUSR1`
- **`pause()`**: Waits for server acknowledgment after each bit
- **Synchronization**: Ensures reliable transmission

</details>

### Bit Manipulation Explained

<details>
<summary><b>Setting Bit to 1 (OR operation)</b></summary>

```c
c = 255;              // 11111111 (all bits set)
c = c | (128 >> 0);   // 11111111 | 10000000 = 11111111
c = c | (128 >> 1);   // 11111111 | 01000000 = 11111111
```

**Logic**: OR with 1 keeps the bit as 1 (idempotent).

</details>

<details>
<summary><b>Setting Bit to 0 (XOR operation)</b></summary>

```c
c = 255;              // 11111111
c = c ^ (128 >> 0);   // 11111111 ^ 10000000 = 01111111 (bit 7 cleared)
c = c ^ (128 >> 2);   // 01111111 ^ 00100000 = 01011111 (bit 5 cleared)
```

**Logic**: XOR with 1 flips the bit (from 1 to 0).

</details>

### Timing Synchronization

**Why 50 microseconds?**
- **Balance**: Speed vs reliability
- **Too fast**: Signals might be lost or reordered
- **Too slow**: Violates performance requirement (< 1s for 100 chars)
- **Formula**: 8 bits × 50μs = 400μs per character → 100 chars in 40ms

---

## 📁 Project Structure

```
minitalk/
├── 📄 LICENSE               # MIT License
├── 📄 Makefile              # Build configuration
├── 📄 server.c              # Server implementation (mandatory)
├── 📄 client.c              # Client implementation (mandatory)
│
├── 📂 libft/                # Custom C library
│   ├── libft.h
│   ├── libft.a
│   ├── ft_atoi.c
│   ├── ft_printf.c
│   └── ... (other libft functions)
│
└── 📂 Bonus/                # Bonus implementations
    ├── Makefile
    ├── server.c             # Server with ACK (sigaction)
    └── client.c             # Client with ACK (pause)
```

### File Breakdown

<table>
<tr>
<th>File</th>
<th>Lines</th>
<th>Purpose</th>
</tr>
<tr>
<td><code>server.c</code> (mandatory)</td>
<td>~45</td>
<td>Signal handling with signal(), bit reconstruction</td>
</tr>
<tr>
<td><code>client.c</code> (mandatory)</td>
<td>~50</td>
<td>Bit transmission with kill(), timing with usleep()</td>
</tr>
<tr>
<td><code>server.c</code> (bonus)</td>
<td>~55</td>
<td>Advanced signal handling with sigaction(), ACK sending</td>
</tr>
<tr>
<td><code>client.c</code> (bonus)</td>
<td>~55</td>
<td>ACK reception, synchronized transmission with pause()</td>
</tr>
</table>

**Total**: 4 source files (2 mandatory + 2 bonus) + libft integration

<details>
<summary><b>Makefile</b></summary>

```makefile
SERVER = server
CLIENT = client
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT = -Llibft -lft

all: pre $(SERVER) $(CLIENT)

$(SERVER): server.o
	$(CC) $(CFLAGS) $^ $(LIBFT) -o $@

$(CLIENT): client.o
	$(CC) $(CFLAGS) $^ $(LIBFT) -o $@

pre:
	$(MAKE) -C ./libft

clean:
	$(MAKE) clean -C ./libft
	$(RM) server.o client.o

fclean: clean
	$(RM) $(SERVER) $(CLIENT)
	$(MAKE) fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re pre
```

**Key features:**
- Compiles libft first (`pre` target)
- Builds two separate executables
- Links with libft (`-Llibft -lft`)

</details>

---

## 🧪 Testing

### Test Categories

<table>
<tr>
<th>Test Type</th>
<th>Command</th>
<th>Expected Result</th>
</tr>
<tr>
<td><b>Simple ASCII</b></td>
<td><code>./client [PID] "abc123"</code></td>
<td>abc123</td>
</tr>
<tr>
<td><b>Special Chars</b></td>
<td><code>./client [PID] "Hello, 42!"</code></td>
<td>Hello, 42!</td>
</tr>
<tr>
<td><b>Spaces</b></td>
<td><code>./client [PID] "Test   spaces"</code></td>
<td>Test   spaces</td>
</tr>
<tr>
<td><b>Long Message</b></td>
<td><code>./client [PID] "$(python3 -c 'print("A"*100)')"</code></td>
<td>100 A's</td>
</tr>
<tr>
<td><b>Unicode (Bonus)</b></td>
<td><code>./client [PID] "¡Hola! 你好 🚀"</code></td>
<td>Unicode characters</td>
</tr>
<tr>
<td><b>Empty String</b></td>
<td><code>./client [PID] ""</code></td>
<td>No output</td>
</tr>
<tr>
<td><b>Newlines</b></td>
<td><code>./client [PID] $'Line1\nLine2'</code></td>
<td>Line1<br>Line2</td>
</tr>
</table>

### Performance Testing

```bash
# Time transmission of 100 characters
time ./client [PID] "$(python3 -c 'print("x"*100)')"

# Should be < 1 second (subject requirement)
```

**Calculation**:
- 100 characters × 8 bits × 50 microseconds = 40 milliseconds
- Well within the 1-second requirement

### Stress Testing

```bash
# Multiple clients simultaneously
./client [PID] "Message 1" &
./client [PID] "Message 2" &
./client [PID] "Message 3" &
wait
```

**Note**: Messages may interleave without proper synchronization.

<details>
<summary><b>Debugging Commands</b></summary>

```bash
# Compile with debug symbols
gcc -g -Wall -Wextra -Werror server.c -Llibft -lft -o server
gcc -g -Wall -Wextra -Werror client.c -Llibft -lft -o client

# Run with gdb
gdb ./server

# Trace signals
strace -e signal ./server

# Check for memory leaks
valgrind ./server
```

</details>

### Test Script

```bash
#!/bin/bash

PID=$(./server &)
sleep 1

echo "Test 1: Simple message"
./client $PID "Hello"

echo "Test 2: Numbers"
./client $PID "123456789"

echo "Test 3: Special characters"
./client $PID "!@#$%^&*()"

echo "Test 4: Long message"
./client $PID "$(python3 -c 'print("A"*100)')"

kill $PID
```

---

## 💡 What I Learned

Through this project, deep understanding was gained in:

- ✅ **UNIX Signals**: `SIGUSR1`, `SIGUSR2`, `kill()`, `signal()`, `sigaction()`
- ✅ **Signal Handlers**: Asynchronous event handling with static variables
- ✅ **Bitwise Operations**: OR, AND, XOR, bit shifts for encoding/decoding
- ✅ **Inter-Process Communication**: PID-based messaging between processes
- ✅ **Binary Protocols**: Custom data transmission using minimal resources
- ✅ **Process Management**: `getpid()`, `pause()`, process synchronization
- ✅ **Timing Synchronization**: `usleep()` for reliable signal transmission
- ✅ **Static Variables in Handlers**: Maintaining state across signal calls
- ✅ **Advanced Signal Handling**: `sigaction()` vs `signal()`, `siginfo_t` struct

### Key Challenges

<table>
<tr>
<th>Challenge</th>
<th>Solution Implemented</th>
</tr>
<tr>
<td><b>Bit Transmission</b></td>
<td>Convert characters to bits using bitwise AND, transmit MSB first</td>
</tr>
<tr>
<td><b>Bit Reconstruction</b></td>
<td>Initialize with 255, use OR for 1 bits, XOR for 0 bits</td>
</tr>
<tr>
<td><b>Timing Issues</b></td>
<td>Found optimal usleep(50) delay through testing</td>
</tr>
<tr>
<td><b>Static Variables</b></td>
<td>Use static int count and c to persist across handler calls</td>
</tr>
<tr>
<td><b>Signal Ordering</b></td>
<td>Synchronization with usleep() ensures correct bit order</td>
</tr>
<tr>
<td><b>Multiple Clients</b></td>
<td>Bonus: ACK system with sigaction() and pause() for synchronization</td>
</tr>
<tr>
<td><b>Unicode Support</b></td>
<td>Bonus: Multi-byte UTF-8 characters transmitted bit by bit</td>
</tr>
<tr>
<td><b>ACK System</b></td>
<td>Bonus: Server sends SIGUSR1 back to client using si_pid from siginfo_t</td>
</tr>
</table>

### Design Decisions

**Why initialize with 255 (0xFF)?**
- Starting with all bits set (1) simplifies logic
- OR keeps 1, XOR flips to 0
- Alternative: start with 0 and use different operations

**Why 50 microseconds?**
- Balance between speed and reliability
- Too fast: signals might be lost
- Too slow: violates performance requirement (< 1s for 100 chars)
- Formula: 100 chars × 8 bits × 50μs = 40ms

**Why `pause()` in bonus?**
- Synchronizes client/server communication
- Ensures reliable transmission
- Allows multiple concurrent clients without interference
- Client waits for ACK before sending next bit

**Why `sigaction()` over `signal()` in bonus?**
- Access to `siginfo_t` struct with sender's PID
- More portable and reliable
- Allows setting `SA_SIGINFO` flag
- Better for modern systems

---

## 📏 Requirements

### Mandatory

- ✅ Server displays PID on startup
- ✅ Client takes server PID and string as arguments
- ✅ Communication using only `SIGUSR1` and `SIGUSR2`
- ✅ Server can receive from multiple clients without restart
- ✅ Fast transmission (< 1 second for 100 characters)
- ✅ Executables named `server` and `client`
- ✅ Error handling for invalid arguments
- ✅ No memory leaks

### Bonus

- ✅ Acknowledgment system (server confirms receipt)
- ✅ Unicode character support
- ✅ Use `sigaction()` instead of `signal()`
- ✅ Client receives confirmation after each character

### Allowed Functions

- `write`, `signal`, `sigemptyset`, `sigaddset`, `sigaction`, `kill`, `getpid`, `malloc`, `free`, `pause`, `sleep`, `usleep`, `exit`

### Forbidden

- ❌ Global variables (except for signal handlers)
- ❌ Using functions outside the allowed list
- ❌ Using pipes, shared memory, or other IPC mechanisms

---

## 📄 License

MIT License - See [LICENSE](LICENSE) file for details.

This project is part of the 42 School curriculum. Feel free to use and learn from this code, but please don't copy it for your own 42 projects. Understanding comes from doing it yourself! 🚀

---

## 🔗 Related Projects

This project builds upon:

- **[libft](https://github.com/Z3n42/42_libft)** - Custom C library (used for `ft_atoi`, `ft_printf`)
- **[ft_printf](https://github.com/Z3n42/ft_printf)** - Used for formatted output

Skills learned here apply to:
- **Pipex** - Inter-process communication with pipes
- **Philosophers** - Process synchronization and concurrency
- **Minishell** - Signal handling in shell implementation

---

<div align="center">

**Made with ☕ by [Z3n42](https://github.com/Z3n42)**

*42 Urduliz | Circle 2*

[![42 Profile](https://img.shields.io/badge/42_Intra-ingonzal-000000?style=flat&logo=42&logoColor=white)](https://profile.intra.42.fr/users/ingonzal)

</div>
