<div align="center">

# 📡 Minitalk

### The purpose of this project is to code a small data exchange program using UNIX signals

<p>
  <img src="https://img.shields.io/badge/Score-125%2F100-success?style=for-the-badge&logo=42" alt="42 Score"/>
  <img src="https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="Language"/>
  <img src="https://img.shields.io/badge/License-MIT-green?style=for-the-badge" alt="License"/>
  <img src="https://img.shields.io/badge/42-Urduliz-000000?style=for-the-badge&logo=42&logoColor=white" alt="42 Urduliz"/>
</p>

*A client-server communication program using only UNIX signals (SIGUSR1 and SIGUSR2) to transmit strings bit by bit.*

[Installation](#%EF%B8%8F-installation) • [Usage](#-usage) • [How It Works](#-how-it-works) • [Implementation](#-implementation-details)

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
- [License](#-license)

---

## 🎯 About the Project

**Minitalk** is a communication system that uses UNIX signals to transmit text between two processes: a **server** and a **client**. The challenge is to send strings character by character using only two signals: `SIGUSR1` and `SIGUSR2`.

### Why Minitalk?

This project introduces fundamental concepts in systems programming:
- **UNIX Signals** - Inter-process communication (IPC)
- **Bitwise Operations** - Encoding characters as bits
- **Signal Handlers** - Asynchronous event handling
- **Process Communication** - PID-based messaging
- **Binary Protocol** - Custom data transmission protocol

The constraint of using only two signals forces you to transmit each character **bit by bit**, creating a custom binary protocol.

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

Since you can only use `SIGUSR1` and `SIGUSR2`, characters are transmitted **bit by bit**:

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

**Client:**
1. Convert server PID from string to integer
2. For each character in the message:
   - For each of the 8 bits:
     - Check if bit is 1 or 0
     - Send `SIGUSR1` (bit = 1) or `SIGUSR2` (bit = 0)
     - Wait 50 microseconds (timing synchronization)

**Server:**
1. Display its PID
2. Register signal handlers for `SIGUSR1` and `SIGUSR2`
3. Enter infinite loop with `pause()`
4. In signal handler:
   - Accumulate bits (8 per character)
   - When 8 bits received, reconstruct character
   - Output character to stdout
   - Send acknowledgment (bonus)

---

## 💻 Implementation Details

### Server Implementation

#### Mandatory Version

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

#### Bonus Version (with ACK)

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

### Client Implementation

#### Mandatory Version

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

#### Bonus Version (with ACK)

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

### Bit Manipulation Explained

#### Setting Bit to 1 (OR operation)
```c
c = 255;        // 11111111 (all bits set)
c = c | (128 >> 0);  // 11111111 | 10000000 = 11111111
c = c | (128 >> 1);  // 11111111 | 01000000 = 11111111
```

#### Setting Bit to 0 (XOR operation)
```c
c = 255;        // 11111111
c = c ^ (128 >> 0);  // 11111111 ^ 10000000 = 01111111 (bit 7 cleared)
c = c ^ (128 >> 2);  // 01111111 ^ 00100000 = 01011111 (bit 5 cleared)
```

### Why Start with 255?

Starting with `c = 255` (all bits set to 1) allows:
- **OR operation** keeps bits that are already 1
- **XOR operation** flips bits to 0
- Simple logic: `SIGUSR1` = keep 1, `SIGUSR2` = flip to 0

---

## 📁 Project Structure

```
minitalk/
├── 📄 LICENSE               # MIT License
├── 📄 Makefile              # Build configuration
├── 📄 server.c              # Server implementation (mandatory)
├── 📄 client.c              # Client implementation (mandatory)
├── 📂 libft/                # Custom C library
│   ├── libft.h
│   ├── libft.a
│   └── (libft sources)
└── 📂 Bonus/                # Bonus implementations
    ├── Makefile
    ├── server.c             # Server with ACK (sigaction)
    └── client.c             # Client with ACK (pause)
```

### File Descriptions

| File | Lines | Purpose |
|------|-------|---------|
| `server.c` (mandatory) | ~45 | Signal handling with `signal()`, bit reconstruction |
| `client.c` (mandatory) | ~50 | Bit transmission with `kill()`, timing with `usleep()` |
| `server.c` (bonus) | ~55 | Advanced signal handling with `sigaction()`, ACK sending |
| `client.c` (bonus) | ~55 | ACK reception, synchronized transmission with `pause()` |

### Makefile Structure

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
```

**Key features:**
- Compiles libft first (`pre` target)
- Builds two separate executables
- Links with libft (`-Llibft -lft`)

---

## 🧪 Testing

### Basic Testing

```bash
# Terminal 1: Start server
./server
# Output: 12345

# Terminal 2: Send message
./client 12345 "Hello World"
```

### Test Cases

#### 1. Simple ASCII
```bash
./client [PID] "abc123"
# Expected: abc123
```

#### 2. Special Characters
```bash
./client [PID] "Hello, 42!"
# Expected: Hello, 42!
```

#### 3. Spaces and Punctuation
```bash
./client [PID] "Test   with   spaces..."
# Expected: Test   with   spaces...
```

#### 4. Long Messages
```bash
./client [PID] "$(python3 -c 'print("A"*100)')"
# Expected: 100 A's
```

#### 5. Unicode (Bonus)
```bash
./client [PID] "¡Hola! 你好 🚀"
# Expected: Unicode characters displayed
```

### Performance Testing

```bash
# Time transmission of 100 characters
time ./client [PID] "$(python3 -c 'print("x"*100)')"

# Should be < 1 second (subject requirement)
```

### Stress Testing

```bash
# Multiple clients simultaneously
./client [PID] "Message 1" &
./client [PID] "Message 2" &
./client [PID] "Message 3" &
wait
```

### Debugging

```bash
# Compile with debug symbols
gcc -g -Wall -Wextra -Werror server.c -Llibft -lft -o server
gcc -g -Wall -Wextra -Werror client.c -Llibft -lft -o client

# Run with gdb
gdb ./server
```

---

## 💡 What I Learned

Through this project, I gained understanding of:

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

1. **Bit Transmission**: Converting characters to bits and reconstructing them
2. **Timing Issues**: Finding right `usleep()` delay for reliable transmission
3. **Static Variables**: Understanding persistence across function calls
4. **Signal Ordering**: Ensuring bits arrive in correct order
5. **Multiple Clients**: Handling overlapping transmissions (bonus)
6. **Unicode Support**: Dealing with multi-byte characters (bonus)

### Design Decisions

**Why initialize with 255?**
- Starting with all bits set (1) simplifies logic
- OR keeps 1, XOR flips to 0
- Alternative: start with 0 and use different operations

**Why 50 microseconds?**
- Balance between speed and reliability
- Too fast: signals might be lost
- Too slow: violates performance requirement (< 1s for 100 chars)

**Why `pause()` in bonus?**
- Synchronizes client/server
- Ensures reliable transmission
- Allows multiple concurrent clients

---

## 📏 Requirements

### Mandatory

- ✅ Server displays PID on startup
- ✅ Client takes server PID and string as arguments
- ✅ Communication using only `SIGUSR1` and `SIGUSR2`
- ✅ Server can receive from multiple clients without restart
- ✅ Fast transmission (< 1 second for 100 characters)
- ✅ Executables named `server` and `client`

### Bonus

- ✅ Acknowledgment system (server confirms receipt)
- ✅ Unicode character support

### Allowed Functions

- `write`, `signal`, `sigemptyset`, `sigaddset`, `sigaction`, `kill`, `getpid`, `malloc`, `free`, `pause`, `sleep`, `usleep`, `exit`

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
