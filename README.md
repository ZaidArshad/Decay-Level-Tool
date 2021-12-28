# Decay-Level-Tool

## Project by Zaid Arshad. Developed from December 2021 to Present

## Description
The Decay Level Tool is a program that helps develop levels for the game “Decay”.

## Experience
I’ve been trying to branch out from consumer based programs to developer based programs. A nice thing about this is that I can easily critique it by using it and seeing the flaws in action. While the technology is the same from the Decay game, the concepts are much different. Everything is about the mouse and there is a lot to track in terms of collision detection making a great learning experience.

## Snappy to smooth dragging
The collision detection needs to change dynamically with where the user clicks so that the drag and drop process is smooth. The origin of the texture changes with every click to allow the user to click on the sprite in any area without it snapping to the center.
<div align="center">
  <img src='https://user-images.githubusercontent.com/52565263/147491796-c7d1bdba-1401-4a72-9fee-a930291bb565.gif' width="600" height="300"/>
</div>

## Dynamic hitboxes
Since the origin is changing to make the dragging smooth, the hitboxes need to match that. As the origin changes, the boundary where the can's position can go also changes.
<div align="center">
  <img src='https://user-images.githubusercontent.com/52565263/147493063-1f2ba307-4524-458e-9a5a-6c7e969965d6.gif' width="300"/>
</div>
