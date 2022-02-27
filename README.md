# Decay-Level-Tool
Project by Zaid Arshad. Developed from December 2021 to January 2022.

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

## Adding and removing platforms
Platforms can be added by clicking the “add” button on the buttons panel. Similarly, they can be removed by first clicking the platform and selecting the “remove” button.
<div align="center">
  <img src='https://user-images.githubusercontent.com/52565263/152641517-1367e31a-c457-4b10-a638-fce894817698.gif' width="700"/>
</div>

## Resizing
When a platform is clicked, it can be resized by clicking the points generated on the corners. Platforms cannot have a width or height smaller than 10 pixels. 
<div align="center">
  <img src='https://user-images.githubusercontent.com/52565263/152641448-5720dfa1-2d29-4fa6-a165-a5e4d83fbb9c.gif' width="300"/>
</div>

## Adjusting properties
When a platform is clicked, the properties panel displays health, x position, y position, width, and height. The health property is made up of a slider that will snap to the nearest tick when the left click is released. The other properties have buttons that can be used to accurately change their respective values.
<div align="center">
  <img src='https://user-images.githubusercontent.com/52565263/152641447-c42fc5db-368d-49f7-a96b-b5b4ef8dcac4.gif' width="300"/>
</div>

## Layering platforms
Platforms can be layered using the “put front” and “put back” buttons. Platforms most recently added will be drawn at the front. 
<div align="center">
  <img src='https://user-images.githubusercontent.com/52565263/152641445-1ca75342-3f3a-4ca2-ae40-29e759010a86.gif' width="700"/>
</div>

## Exporting levels
Once a level has been made, it can be exported with the “EXPORT” button. Your default .txt editor will open and display the text in the format of:
```
Player_Y Player_Y
HEALTH WIDTH HEIGHT XPOS YPOS
HEALTH WIDTH HEIGHT XPOS YPOS
HEALTH WIDTH HEIGHT XPOS YPOS
```
The first line is the position of where that platform would start, and the subsequent lines would be the details of each platform. From front to back the platforms will be drawn based on the order in the file.
<div align="center">
  <img src='https://user-images.githubusercontent.com/52565263/152641446-57412b87-7dc6-47bd-a8af-3172338a2dd8.gif' width="900"/>
</div>
