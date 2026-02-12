*This project was created by ramarti2 and is part of the 42 School curriculum.*
# 🍝 Philosophers

> A multithreading and synchronization project based on the Dining Philosophers problem.

---

## 🧠 The Problem

- `N` philosophers sit at a round table.
- There are `N` forks.
- Each philosopher needs to hold **two forks** (left and right) to eat.
- After eating, they sleep.
- After sleeping, they think.
- If a philosopher doesn’t eat within `time_to_die`, they die.
- The simulation stops when:
  - A philosopher dies, or
  - All philosophers have eaten `number_of_times_each_must_eat` times (optional argument).

---

## 📚 Overview

The **Philosophers** project explores threading and process synchronization based on the *Dining Philosophers Problem*.

The goal is to simulate philosophers sitting around a table who alternate between:

- 🍴 Eating  
- 💭 Thinking  
- 😴 Sleeping  

Since Forks are shared resources, and each philosopher needs to forks to eat, improper handling can lead to:

- Deadlocks (e.g. all philosophers holding 1 fork and endlessly waiting for the other)
- Starvation  (a philosopher ends up waiting for a fork for too long and dies of starvation)
- Race conditions (two or more threads trying to access the same resource simultaneously)

This project focuses on:

- Thread creation using `pthread`
- Mutex synchronization
- Precise timing management
- Deadlock avoidance
- Resource sharing

---
### Parameters

| Argument | Description |
|----------|------------|
| `number_of_philosophers` | Number of philosophers and forks |
| `time_to_die` | Time (ms) before a philosopher dies if not eating |
| `time_to_eat` | Time (ms) spent eating |
| `time_to_sleep` | Time (ms) spent sleeping |
| `number_of_times_each_must_eat` | (Optional) Simulation stops after each philosopher eats this many times |

---

## 🧵 Threading Model

- Each philosopher is represented by a **thread**
- Each fork contains and is protected by a **mutex**
- A monitoring thread (called the "grim_reaper") checks:
  - Death conditions (and prints the death of a philospher);
  - Completion conditions;
 and terminates the simulation.

### Functions Used

- `pthread_create`
- `pthread_join`
- `pthread_mutex_init`
- `pthread_mutex_lock`
- `pthread_mutex_unlock`
- `gettimeofday` (or equivalent timing function)

---

## 🛑 Deadlock Prevention Strategy

To prevent deadlocks, one of the following strategies is used:

- Fork locking order (global ordering)
- Odd/even philosopher fork acquisition
- Using the monitoring thread to terminate the simulation

Example strategies:
- Tiny delay to odd philosophers so the evens get to the forks first
- Even philosophers take the left fork first
- Odd philosophers take the right fork first
- Larger delay to give enough time for thread creation so that all threads start simultaneously

---

## 🖥 Example Output

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
410 2 died
```

Output format:

```
timestamp_in_ms philosopher_id action
```

---
## Instructions
### 🏗 Compilation

```bash
make
```

Clean object files:

```bash
make clean
```

Full clean:

```bash
make fclean
```

Recompile:

```bash
make re
```

### ⚙️ Execution
To execute, run the program (philo) with the following arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_must_eat]
```
#### (!) All times must be more than 60ms!
#### (!!) The number of philosphers can't be less than 1 or more than 200!
#### (!!!) If given, the number of meals can't be less than or equal to 0!

## 🧪 Testing Examples

```bash
./philo 1 800 200 200
./philo 5 800 200 200
./philo 5 800 200 200 5
./philo 200 800 200 200
```

---

## 🛠 Requirements (42 School)

- No global variables
- No data races
- No deadlocks
- Proper mutex handling
- Norm compliant
- No memory leaks

---

## 📈 Concepts Covered

- Multithreading
- Mutex synchronization
- Race condition prevention
- Deadlock avoidance
- Resource management
- Time-sensitive simulation
- Thread monitoring

