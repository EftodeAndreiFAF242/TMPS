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

## How to run

The project needs only a C++ compiler (g++).

```
g++ main.cpp -o tmps
./tmps
```

The program shows a menu. Type the number of a laboratory work to run its demo, or `0` to
exit.

## Files

```
main.cpp    the menu and the demo of each laboratory work
Lab1/       laboratory work 1: one file for each SOLID principle
```
