# rays
In high school (ages ago) I have written a simple raytracing application using "Oberon" (a derivation of Modula) https://en.wikipedia.org/wiki/Oberon_(programming_language)

For a C++ nano degree I took the task to design and implement a similar application using C++. Especially the efficiency and parallel processing techniques are key in this approach.

The principles and mathematics are derived from the book "Computer Graphics from Scratch" https://gabrielgambetta.com/computer-graphics-from-scratch/

## Usage
rays [options]
  -h    this help
  -f    output file name ("../image.png" default)
  -b    number of mirror bounces to be considered (default 5)
  -t    number of threads to render in parallel (default 4)

### Limitation
The current implementation only supports square images, where the width is equal to the height.


## Project Structure

### Own basic classes
These classes have been defined to provide basic functionality to calculate in 3D space and colors. The existing https://opencv.org approaches have not been used in order to be independent from the visualization framework.

#### Coordinate3d (Point in 3D space)
The class `Coordinate3d` encapsulates 3 values and is used to compute points in the 3D space (x, y, z).

#### Ray3d
The class `Ray3d` is derived from `Coordinate3d` and uses the inherited coordinate as the origin of a ray. The member `_direction` is used to point in the direction of the ray.

#### Color3d
Very similar to `Coordinate3d` from a computation point of view, however defined in an own class to get type safety.
The material kind is used to distinguish different kinds of materials (plain, mirror, checkered, ...)

