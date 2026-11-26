# philosophers

> The **dining philosophers** problem, simulated with POSIX threads and mutexes in C.

![C](https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white)
![pthreads](https://img.shields.io/badge/POSIX-threads-555555?style=flat)

## About

A number of philosophers sit around a table with one fork between each pair. To eat, a philosopher
needs both neighbouring forks; after eating they sleep, then think. If someone goes too long without
eating, they die and the simulation stops. The challenge is to keep everyone alive **without deadlocks
or data races**, and to report a death within a few milliseconds.

## How it works

- every philosopher is a **thread**, every fork is a **mutex**
- forks are picked up in an order that depends on the philosopher's id, which prevents a deadlock
- odd philosophers start with a short delay so neighbours don't all grab forks at once
- a **monitor** checks the time since each philosopher's last meal and stops the simulation on a death or once everyone has eaten enough
- shared state (status, last meal time, printing) is protected by its own mutexes
- a custom sleep function keeps timing accurate, and the single-philosopher case is handled separately

## Build & run

```bash
make
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [meals_per_philosopher]
```

Times are in milliseconds, and the program accepts up to 200 philosophers.

```bash
./philo 5 800 200 200        # should run forever
./philo 5 800 200 200 7      # stops once everyone has eaten 7 times
./philo 4 310 200 100        # a philosopher dies
```

## Output

```
0 2 has taken a fork
0 2 has taken a fork
0 2 is eating
200 2 is sleeping
...
```

Each line is `<timestamp_ms> <philosopher> <action>`.

---

<sub>Part of the <a href="https://www.codam.nl/">Codam</a> (42 network) curriculum.</sub>
