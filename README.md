# ChinczykQt (Ludo) — Qt 6 / C++ (Version 1.0)

## Features (v1.0)
- 2–4 players (selectable before starting a new game)

- Classic cross board layout (15×15 grid style)

- Dice roll + turn system

- Capturing (“beating”):
  
    - You can capture an opponent’s pawn if there is exactly one enemy pawn on the destination tile
  
    - No capture if the destination has a blockade (two pawns of the same color)

- Blockade rule:

     - If a tile contains two pawns of the same color, it becomes a blockade

     - Other pawns cannot land on it and cannot pass through it

- Home lane (our ruleset):

    - The home area consists of 4 slots: 52, 53, 54, 55

    - A pawn must enter home exactly (no overshooting)

    - Pawns cannot stack in home; you can’t jump over occupied home slots

- Win condition (our ruleset):

    - A player wins when all 4 pawns are placed inside home slots 52–55

- End-of-game dialog:

    - Displays the winner color

    - Offers New Game and (when applicable) Continue (play for further places)

## Notes / Roadmap Ideas
This is v1.0 and meant as a solid playable base. Possible future improvements:

- Better board visuals (textures, icons, smoother animations)

- Sound effects and turn indicators

- Online multiplayer / LAN mode

- Saving/loading game state

- Optional rule presets (different Ludo variants)
