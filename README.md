# Philo Project

## Introduction
Philo is a project from 42 school that involves solving the classic **Dining Philosophers Problem** using multithreading. The goal is to manage concurrency, avoid deadlocks, and ensure efficient resource utilization.

## Features
- Implements the Dining Philosophers problem
- Uses pthreads for concurrency
- Mutexes for preventing race conditions
- Handles different simulation parameters
- Ensures no deadlock or starvation

## Installation
### Prerequisites
- A Unix-based system (Linux/macOS recommended)
- GCC or Clang compiler
- Make
- pthreads library

### Steps to Install
1. Clone the repository:
   ```sh
   git clone https://github.com/elmehdibelfkih/philo.git
   cd philo
   ```
2. Compile the project:
   ```sh
   make
   ```
3. Run the program:
   ```sh
   ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
   ```
   Example:
   ```sh
   ./philo 5 800 200 200
   ```

## Parameters Explanation
- `number_of_philosophers` - Total number of philosophers.
- `time_to_die` - Time (in milliseconds) after which a philosopher dies if they haven’t eaten.
- `time_to_eat` - Time (in milliseconds) it takes a philosopher to eat.
- `time_to_sleep` - Time (in milliseconds) a philosopher sleeps before thinking again.
- `[number_of_times_each_philosopher_must_eat]` (Optional) - If provided, simulation stops when each philosopher has eaten this many times.

## Key Concepts
- **Threads:** Each philosopher runs as an independent thread.
- **Mutexes:** Used to synchronize fork access and prevent race conditions.
- **No Deadlocks:** Proper locking/unlocking prevents deadlocks.
- **Synchronization:** Timers and thread management ensure proper execution.

## Common Issues & Debugging
- **Philosophers not eating:** Check if the forks are being locked/unlocked properly.
- **Unexpected deaths:** Ensure the correct timing logic is implemented.
- **Program not stopping:** Verify if the stopping condition is correctly handled.

## Contributing
Pull requests are welcome. Follow best practices and document any major changes.

## License
This project is licensed under the MIT License - see the LICENSE file for details.

## Authors
- Your Name (@elmehdibelfkih)

