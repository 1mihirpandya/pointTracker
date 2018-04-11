# Project Proposal

# Point Tracking

The project will essentially be based on point of reference tracking. Using the computer's camera, the program will track a user defined point across the screen, allowing interesting analysis to be done and findings to be made.

## Application Usage
The OpenFrameworks application will use the computer's camera using `ofVideoGrabber`. The user will then choose a point on the screen to track. After initialization, the user may move the point around the screen while being tracked.

## Point Tracking
There should be two main types of point tracking--simple "memoryless" tracking and memory tracking. The former will not remember any of the previous locations of the point, and will simply track it's point location across the screen. The latter, however, will remember the entire trail that the pointer followed, and be able to highlight the path it has taken.

## Applications
Point tracking on screens has been a task engineers toil over--be it tracking faces in Adobe After Effects or tracking fingers on Google Hangouts, on screen tracking is a very useful skill. It could be used for learning (drawing on a shared computer window), forensic tracking (tracking a person in a car crash), and more. Of course for this project, the tracking will all be done real time based on the computer's camera.

## Scope
The scope of this project is containted to discerning and tracking user defined points in real time using the computer's camera. If time permits, I would like to extend the project to pre-recorded videos, and possibly peer-to-peer point tracking (two computers).

## Libraries
### `ofxSpatialHash`
`ofxSpatialHash` is used for finding the nearest neighbors. Could be helpful for path tracking on 2D Arrays.

### `ofxGVF`
`ofxGVF` is a gesture variation follower. Could be a good reference or a library I could use.

### `ofxGrt`
`ofxGrt` is a gesture recognition library. Could be a good reference or a library I could use.

### `ofxAssignment`
`ofxAssignment` is a library used to match point clouds. Could be a good library to use for path tracking.

