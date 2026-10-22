# TMPS — Laboratory Works

- **Course:** Software Design Techniques and Mechanisms (TMPS)
- **Author:** Eftode Andrei, FAF-242
- **Professor:** Istrati D.

One small application grows through the semester: the backend of a system where citizens
report city problems (a pothole, a broken street light, dumped garbage) and city hall
handles them. It has no graphical interface on purpose, because the course is about how
the code is designed.

Each laboratory work has its own folder, with its own report.

| Laboratory work | Topic | Folder |
| --- | --- | --- |
| 1 | SOLID principles | [Lab1](Lab1/) |
| 2 | Creational design patterns | [Lab2](Lab2/) |

## How to run

The project needs only a C++ compiler (g++).

```
g++ main.cpp -o tmps
./tmps
```

The program shows a menu. Each laboratory work can run in two ways:

- **the ready example**: the data is already written in the code, so every case is shown;
- **your own data**: you type the reports in the console, and the same classes handle them.

Type `0` to exit.

## Files

```
main.cpp    the menu, the ready example of each laboratory work and the version with your own data
Lab1/       laboratory work 1: one file for each SOLID principle
Lab2/       laboratory work 2: one file for each creational pattern
```
