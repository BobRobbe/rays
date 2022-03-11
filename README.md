# rays
In high school (ages ago) I have written a simple raytracing application using "Oberon" (a derivation of Modula) https://en.wikipedia.org/wiki/Oberon_(programming_language)

For a C++ nano degree I took the task to design and implement a similar application using C++. Especially the efficiency and parallel processing techniques are key in this approach.

The principles and mathematics are derived from the book "Computer Graphics from Scratch" https://gabrielgambetta.com/computer-graphics-from-scratch/

## Usage
**rays** [options]
  -h    this help
  -f    output file name ("../image.png" default)
  -b    number of mirror bounces to be considered (default 5)
  -t    number of threads to render in parallel (default 4)
  -s    size of the rendered image (default 800)

##### Limitation
The current implementation only supports square images, where the width is equal to the height, thus only one size attribute is needed.


## Project Structure

### Own foundation classes
These classes have been defined to provide basic functionality to calculate in 3D space and colors. The existing https://opencv.org approaches have not been used in order to be independent from the visualization framework.

#### Coordinate3d (Point in 3D space)
The class `Coordinate3d` encapsulates 3 values and is used to compute points in the 3D space (x, y, z).

#### Ray3d
The class `Ray3d` is derived from `Coordinate3d` and uses the inherited coordinate as the origin of a ray. The member `_direction` is used to point in the direction of the ray.

#### Color3d
Very similar to `Coordinate3d` from a computation point of view, however defined in an own class to get type safety.
The material kind is used to distinguish different kinds of materials (plain, mirror, checkered, ...)

### Render Objects
`RenderObject` is the base class to define various objects to be included the the scene definition. Each `RenderObject` has a coordinate to define the origin and a color to define the color and material.

Two virtual methods provide specific implementation for the different object sub-classes:

* `hits_render_object` checks whether a specific ray hits this object
* `get_color` calculates the color a ray will see when it hit that object

The major difference is that `hits_render_object` returns the distance to the closest hit object, while `get_color` may need to process further rays in case there is a mirror material on the object which is hot.

#### Sub-Classes of Render Objects
Currently supported object kinds inheriting from `RenderObject` and providing specific overrides are `RenderSphere`, `RenderPlain`, `RenderSky`.

### Scene

The class `Scene` is implementing the actual ray-tracing algorithm.

The method `ray_trace` gets a ray object and checks whether there are any objects which intersect with that ray. The closest hit point with respect to the ray origin is considered for further processing.

If there was a hit of the ray with an object the color of the hit point is calculated.

The method `compute_part` is designed to calculate a part of the final image sliced in horizontal direction.
This method can be invoked in worker threads and computes specific parts of the final image.

##### No need for mutex
Because each potential `compute_part` thread calculates a different part of the image there is no need to "protect" the shared resource (image), as each thread will write to a different part of that single image.

### main
The `main()` of the `rays` executable performs several steps:
* parse potential arguments values (see "usage"), default value apply if not given during start
* create an example scene using some lights, spheres, plain, and a sky.
* define the camera position (0,0,0)
* based on the number of threads to be started partition the image into slices
* start for each slice a separate thread to calculate that part of the image
* wait for all the started threads to finish
* calculate the time it took to render the image and display the time value
* display the image and save the image to a file
* wait for a key stroke

## C++ Capstone Project Rubric

##### README (All Rubric Points REQUIRED)
Done

##### Compiling and Testing (All Rubric Points REQUIRED)
Done

##### Loops, Functions, I/O
**The project reads data from an external file or writes data to a file as part of the necessary operation of the program.**
Final image is stored in a file.

**The project accepts input from a user as part of the necessary operation of the program.**
Input arguments during program start are processed.

##### Object Oriented Programming
**The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks.**
Example `RenderObject` and its sub-classes.
**All class data members are explicitly specified as public, protected, or private.**
Example `RenderObject` and its sub-classes.
**One member function in an inherited class overrides a virtual base class member function.**
E.g. `RenderSphere` overrides virtual methods of `RenderObject`.


##### Memory Management
**For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined.**
See `Color3d`, `Coordinate3d`, `Ray3d`, `RenderObject`

**The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr. The project does not use raw pointers.**
`RenderObject`s are created (in `main()`) and stored as `shared_ptr` in `Scene`.

##### Concurrency
**The project uses multiple threads in the execution.**
Rendering of the image can be performed in a configurable number of threads.


No protection mechanism is needed as the threads operate on different parts of the final image.

