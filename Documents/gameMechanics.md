# Geometry Dash Mechanics

<details>
<summary><b>Table of Contents</b></summary>

- [Geometry Dash Mechanics](#geometry-dash-mechanics)
  - [1. Introduction](#1-introduction)
  - [2. Final game mechanics](#2-final-game-mechanics)
    - [2.1. Player](#21-player)
    - [2.2. Obstacles](#22-obstacles)
    - [2.3 Features](#23-features)
  - [3. MVP](#3-mvp)
    - [3.1. Only main mode](#31-only-main-mode)
    - [3.2. Start Point](#32-start-point)
    - [3.3.  Point](#33--point)
    - [3.4. White Square](#34-white-square)
    - [3.5. Screen Rolling](#35-screen-rolling)
    - [3.6. Ground](#36-ground)
    - [3.7. Jump](#37-jump)
    - [3.8. Death](#38-death)
    - [3.9. Black Box Obstacle](#39-black-box-obstacle)
  - [4. Future Improvements](#4-future-improvements)
    - [4.1. Player](#41-player)

</summary></details>

## 1. Introduction

In this document we will be discussing the mechanics of our remake of the game Geometry Dash.

## 2. Final game mechanics

### 2.1. Player

The player will be able to use multiple type of characters that behave differently. The player will be able to select through a variety of characters, colors, styles...

The original cosmetics are:

**Main character**

![Icon](img/icon.png)

**Ship:**

![Ship](img/ship.png)

### 2.2. Obstacles

There will be different types of obstacles that the player will have to avoid. We will only do the black box obstacle and the spikes obstacle. The black box obstacle and spike will look like this:

![Block](img/block.png) ![Spike](img/spike.png)

### 2.3 Features

We plan to add coins that the player can collect to increase their score. The coins will look like this:

![Coin](img/coin.png)

We also plan to add an attempt counter that will keep track of the number of times the player has died.

## 3. MVP

### 3.1. Only main mode

As a MVP only the main mode would be implemented. It consist in a die or retry mode.

### 3.2. Start Point

The game should have a start point where the player spawn at the launching of the game and every time he needs to respawn.

### 3.3.  Point

The game need a final point to end the level and close it.

### 3.4. White Square

The player would be represented as a white square since it will not contain any designed.

### 3.5. Screen Rolling

The screen will roll from left to right but it will not decomposed and composed the level when it appear in the screen, it will just roll as a band.

### 3.6. Ground

A ground will be implemented as well as a gravity system like in the original game.

### 3.7. Jump

The jump feature will be indispensable since it's a plateform game which need to avoid obstacles by jumping over them.

### 3.8. Death

In the case you hit an obstacle side-on for a square, you should die and restart the game at the start point.

### 3.9. Black Box Obstacle

The obstacle previously mentionned would only be black square for the mvp.

## 4. Future Improvements

### 4.1. Player

We will add new character types, that won't be playable in an early stage of the game, such as:

**Ball:**

![Ball](img/ball.png)

**Robot:**

![Robot](img/robot.png)

**Spider:**

![Spider](img/spider.png)

**Triangle:**

![Triangle](img/triangle.png)

**UFO:**

![UFO](img/ufo.png)

**Color customization:**

The user will be able to choose within multiple available colors to customize the appearance of his character. A customization shop will be available to the user to do so.
