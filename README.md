# rays
In high school (ages ago) I have written a simple raytracing application using "Oberon" (a derivation of Modula) https://en.wikipedia.org/wiki/Oberon_(programming_language)

For a C++ nano degree I took the challenge to design and implement a similar application using C++. Especially the efficiency and parallel processing techniques are key in this approach.

The principles and mathematics are derived from the book "Computer Graphics from Scratch" https://gabrielgambetta.com/computer-graphics-from-scratch/

## Project Structure

#### Coordinate3d (Point in 3D space)
The class `Coordinate3d` encapsulates 3 values and is used to compute points in the 3D space (x, y, z).

#### Ray3d
The class `Ray3d` is derived from `Coordinate3d` and uses the inherited coordinate as the origin of a ray. The member `_direction` is used to point in the direction of the ray.

#### Color3d
Very similar to `Coordinate3d` from a computation point of view, however defined in an own class to get type safety.

