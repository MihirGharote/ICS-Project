# ICS-Project

## Introduction
The project consists of a fantasy genre RPG (Role-Playing Game) inspired by DnD, played entirely within a terminal emulator.

## Gallery

<img width="1600" height="698" alt="demo_story" src="https://github.com/user-attachments/assets/dc74f29a-7286-49df-a9c4-20795194efdb" />
<img width="1857" height="700" alt="demo_combat" src="https://github.com/user-attachments/assets/54274ba6-a190-40e2-893e-8fca88780d2e" />

https://github.com/user-attachments/assets/e07fe2e2-f9e1-4052-a838-8cb9c576b9b6

### Presentation
https://docs.google.com/presentation/d/1dIKrOpW0QEEE6nnRUBd-4ga7u6vTIpcs/

## Technical Details
The project is implemented entirely in C. The main library used is `<ncurses.h>`, which is the de facto standard of making TUIs (Text User Interfaces). Apart from that, the standard library was also used, comprising `<stdlib.h>`, `<string.h>`, `<time.h>`, etc.

The combat system is implemented via nested structs inside structs: this system tries to emulate object oriented programming in other language, as it's a natural way to develop games.

The choice system uses blocking, no-echo calls to prevent the user from inputting garbage values, and ensuring choices are made properly.

The animations were implemented by doing changes delayed by a few milliseconds to give the impression of movement.

## Team Member Contributions
- Mihir: Overall orchestration, game design, ncurses rendering
- Samarth: Combat design
- Rudri: Story writing and combat
- Khyati: Game choices and mainloop
- Priyal: Minigames
- Riya: ASCII Art design
