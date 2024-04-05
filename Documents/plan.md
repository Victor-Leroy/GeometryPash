# plans

## MVP

1. make a square (white)
2. make it jump
3. make an other square (black)
4. make the first square move right
5. make collision between the two square
6. make the game restart on death condition
7. make an end condition
8. make a level with several platform and stuff

## technical documentation

**Level class**

    x,y restart position
    array of all the obstacles
    number of restarts
    background sprite


    restart()

   **Block Class**
    sprite
    size
    x, y position

   **Player class : block**
    jump function,
    move right function -> called every frame
    colision detection -> check if two line intersect

   **obstacle class : block**
    // the direction from which can it kills you
    death horizontal (bool)
    death vertical (bool)

   **EndFlag class : block**
    victory function()
