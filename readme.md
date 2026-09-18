# Ray Tracer

A simple **ray tracer written from scratch in C++**, built to explore the fundamentals of computer graphics and physically-based rendering.

The project is based on concepts from *Ray Tracing in One Weekend* and implements a CPU-based renderer capable of rendering spheres with different materials, reflections, refractions, anti-aliasing, and depth of field.

## Final Render

<p align="center">
  <img src="media/image.png" alt="Final Ray Tracer Render" width="800">
</p>

## Features

* Ray generation from a virtual camera
* Ray-sphere intersection
* Surface normals
* Diffuse materials
* Metallic materials
* Dielectric / glass materials
* Reflection
* Refraction
* Recursive ray scattering
* Anti-aliasing
* Randomized sampling
* Depth of field
* Adjustable camera parameters
* PPM image output

## Tech Stack

* **C++**
* **C++17**
* **Standard Library**
* **PPM** image format

No external graphics or rendering libraries are required. The renderer generates the image directly on the CPU.

## Project Structure

```text
Ray_tracer/
├── header/
│   ├── camera.h
│   ├── color.h
│   ├── hittable.h
│   ├── hittable_list.h
│   ├── interval.h
│   ├── material.h
│   ├── ray.h
│   ├── sphere.h
│   ├── vec3.h
│   └── ...
│
├── src/
│   ├── ...
│   └── ...
│
├── assets/
│   └── final_render.png
│
├── basic_ppm.cpp
├── image.ppm
└── README.md
```

## How It Works

The renderer follows the basic ray-tracing pipeline:

```text
                 Camera
                    │
                    ▼
              Generate Ray
                    │
                    ▼
          Ray / Object Intersection
                    │
                    ▼
              Hit Detection
                    │
                    ▼
             Surface Normal
                    │
                    ▼
               Material
              /    |     \
             /     |      \
        Diffuse  Metal  Dielectric
             \     |      /
              \    |     /
               ▼   ▼    ▼
            Scatter Ray
                 │
                 ▼
          Recursive Bounce
                 │
                 ▼
          Accumulate Color
                 │
                 ▼
             Pixel Color
                 │
                 ▼
             Image Output
```

For every pixel, one or more rays are generated from the camera into the scene.

When a ray intersects an object, the renderer calculates the intersection point and surface normal. The material at that point determines how the ray behaves.

Reflective and transparent materials can generate additional rays, allowing light to bounce through the scene recursively.

## Materials

### Diffuse

Diffuse materials scatter incoming rays randomly around the surface normal.

This produces the soft, matte appearance of materials such as:

* Walls
* Paper
* Stone
* Unpolished surfaces

### Metal

Metallic surfaces reflect rays according to the reflection direction, with an optional **fuzz factor** controlling how rough the reflection is.

### Dielectric

Dielectric materials simulate transparent objects such as glass.

The renderer handles:

* Refraction
* Reflection
* Index of refraction
* Total internal reflection

## Anti-Aliasing

Multiple rays are sampled for each pixel instead of using a single ray.

```text
             Pixel
        ┌─────────────┐
        │ •  •     •  │
        │    •  •     │
```
