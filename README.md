# Point Tracking

The project is essentially point and motion tracking using CV. Using the computer's camera, the program will look for a specific user-defined point on the screen, and will draw on the screen based on the movement of the marker.

# Run Requirements/Instructions

The pointTracker application runs in C++ and uses OpenFrameworks. To run this project, you will have to download openFrameworks. Once it is downloaded, move the `pointTracker` folder into `OpenFrameworks/apps/myApps/`. Open the application using Xcode and Visual Studio for Macs and Windows, respectively. Simply run the program, and you are ready to use pointTracker.

# Using the Application

## Selecting a point to track
When the application starts running, click the desired tracking point on the screen. Now, the point will be tracked when moved. Avoid white backgrounds and rooms with many objects that are the same color as the point being tracked. The color being tracked can be seen in the colored square at the top right corner of the screen.

## Changing color
By pressing 's', a color slider will appear. Adjust the RGB values to change the color of the line being drawn. By pressing s again, the color slider will dissapear.

## Using shapes
Pressing 'r', 'c', or 't' will create a rectangle, circle, or triangle on the screen (respectively). The shape will follow the point until "placed" at a certain location. To place the shape, simply move the point being tracked closer towards the screen, almost like a "click".

## Clearing the screen
Press 'd' to delete all the lines on the screen. Press 'b' to clear the current line.

# Software/Tools

As mentioned, this project runs in C++ and uses OpenFrameworks. Point tracking is done using OpenCV and the distance formula. "Clicks," or placing objects is done using depth perception (also based on OpenCV).
