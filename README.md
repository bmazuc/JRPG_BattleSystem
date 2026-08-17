# JRPG\_BattleSystem



A simple 2D game engine and a demo game done with it.

Game is a simple JRPG battle where you should defeat as many enemies as possible before you die. Once all three enemies are dead, new ones spawn.



The ‘Flee’ button allows you to end the battle manually.



Each character has a unique ability:

\- Regenerate: restores health and mana to the target.

\- Spell: deals magic damage to the target.

\- All or Nothing: the lower the character’s health, the more damage they deal to the target. 



Code will be separated in two folders :



* Engine : contains management of SDL, OpenGL, etc. Should not depend on any Game files. Goal is to be able to reuse the code as-is in other projects.
* Game : contains game logic. Is dependant of engine.



Libs :

&#x09;- SDL3 3.4.2

&#x09;- glew 2.3.1

&#x09;- glm 1.0.3

&#x09;- freetype 2.9.1

