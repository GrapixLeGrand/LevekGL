The goal is to implement an instanced renderer over the same given mesh. For example,
we will be able to use a sphere and render it from an array of positions.

I think its worth implementing two possibilities: specify a single color for all instances
or use a per instance color. This requier two shaders.

We will stick to using a single mesh for now since it looks the simplest.

- Is this the right way of spawning a lot of spheres? Let's say yes for now.
  - It could be interesting later to compare it with other technics.

What we need:
- a sphere mesh (in obj for now)
- calls and shader calls to draw a lot of them
- at the end report performances

1 - Load the sphere mesh (later will do an algorithm once this is working)
2 - Shader with attrib for position only => shift the spheres (no rotations of whatsoever the sphere will be drawn at its size)
3 - layout for instance figure out
4 - build vertex array with: 1 the vb/ib of the sphere (pos + index + normal) + 2 all the positions (vec3)
5 - render with camera movements

