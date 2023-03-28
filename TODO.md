# Todo

## world
- [x] Change the `Actor` class from inheritance to composition.
- [x] Add shadow sprite to `Actor`.
- [x] Add TextureManager.
- [x] Copy battle sprites to base textures, add battle action.

## soldier
- [x] Introducing collision detection.
- [x] stop if hit.

## ugrid
- [x] optimizing.
- [x] show uniform-grid border.

## battle
- [x] if encounter enemy，attack.
- [x] add finite state machine for actions.
- [x] play attack/hit animation when battle.
- [x] using more atcions.
- [x] if defend or jump, not minus hp.
- [x] if dead, no collision handling, and disappear.
- [x] when attacking, crash into the enemy.
- [x] if too close, pull away; if too far, get closer. 

## all
- [x] rewrite all projects, adapt gsl, extract common classes and move to common.
- [x] release v1.5.1 builds for windows.
- [ ] the system has gradually become more complex, considering whether to introduce the ECS library such as entt.