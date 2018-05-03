# Project Proposal

# Point Tracking

The project will essentially be based on point of reference tracking. Using the computer's camera, the program will look for a specific color (bright blue) on the screen, and will draw on the screen based on the movement of the marker.

## Scope
For the time being, the scope is restricted to allowing the user to draw on the screen using a bright blue marker (unless time permits).

## Update 1:
Created project structure and created line drawing/making functionality using a keyboard and a mouse. This is drawn on the image from videoGrabber.

## Update 2:
Created point tracking via green colored pen. Updated point tracking algorithm to create smoother lines with less noise. Added a clear function that safely deletes all the lines drawn on the heap and clears the screen. Discontinuous lines can be drawn.

## Update 3:
Switched to using the Euclidian Formula for color matching. The point/color tracking is much more accurate.

## Update 4:
Switched from using ofPolyline to using ofPath. Colors can be changed and the line width can be changed. Added a color picker to allow users to change line color.

## Update 5:
Changed the point tracking algorithm again. Now, the point is found/tracked using a combination of HSV filtering and the euclidian formula. The desired color is matched by hue and then the euclidian formula is used to find the closest match out of the options provided.

## Update 6:
Added the ability to pick any color on the screen to track.

## Update 7:
Added the ability to drop shapes into the frame.

## Update 8:
Added the ability to create a shape (rectangle, circle, triangle), drag it to the desired location, and then "drop" it there by "clicking" the screen with the marker. Used depth perception.
