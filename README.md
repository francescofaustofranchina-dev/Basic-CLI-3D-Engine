# 🌐 Basic 3D Engine (CLI-based)
Last update: 30/09/2025
## ❗ Disclaimer
The engine currently works only on Linux systems. Furthermore, while it is capable of correctly displaying meshes (`.obj` files), it lacks certain features such as clipping.
## 📄 Introduction
This engine is a project I developed over about two months to learn C++ while also studying the fundamentals of 3D graphics. Because of this learning focus, I deliberately chose not to use any external graphics libraries. 

Although I don't consider the engine to be "professional" software, I put significant effort into writing clean, readable, and modular code. Furthermore, I designed the engine with extensibility in mind, so that new features and improvements can be added more easily in the future.
## ✔️ Implemented features
- **Basic math primitives and operations:** includes custom implementations of 2D and 3D vectors, matrices, and essential operations such as dot products, cross products, and matrix transformations.
- **Global delta time:** a simple system to track and use frame time differences, allowing for time-independent transformations.
- **Standard mesh representation:** meshes are defined using a conventional structure that separates vertex data from triangle definitions, following the typical vertex/index buffer layout used in real-time graphics engines:
  - All vertices are stored in a *vertex buffer*
  - Triangles are defined using an *index buffer*, where each entry holds the indices of the three vertices that form a triangle
  - Additional per-triangle data such as normals and brightness values are stored separately
- **OBJ file parser:** the engine includes a custom `.obj` file parser that supports vertex positions (v), normals (vn), and faces (f) in the v//vn format. The parser ensures that each unique combination of position and normal is stored only once, using a hash-based lookup to avoid vertex duplication.
- **Geometry processing:** given a mesh, the engine can:
  - Apply basic transformations (translation, rotation, scaling)
  - Project the 3D vertices into 2D screen space
  - Perform backface culling to improve performance by skipping non-visible triangles
  - Apply flat shading to simulate how directional light interacts with the surface of the mesh
- **Rasterization:** the engine rasterizes each triangle using a bounding box scan technique. It also implements a Z-buffer to ensure correct depth rendering, displaying only the closest triangles to the camera.
Pixel brightness is represented using monochromatic ASCII characters, creating a visually intuitive output in the terminal.
## ❌ Missing features
- Clipping
- Rendering multiple meshes at the same time
- Advanced shading techniques
- Cross-platform support
## ⌨️ Languages used
- C++
## 🔧 Tools used
- Visual Studio Code
## ✏️ My role in the project
I developed the entire project from the ground up.
## 🖥️ How to run the engine
1. Create a directory on your system where you want to place the project.
2. Download the repository into that directory.
3. Open the terminal and move into the project folder.
4. Run the *engine* executable, passing the path to an `.obj` mesh file as the only argument.
For example:
```bash
./engine assets/Cube.obj
```
To help users use their meshes, the following guide shows how to export a model from Blender using the correct settings:
1. Open your mesh in Blender.
2. Go to:  
   **File → Export → Wavefront (.obj)**
3. In the export panel (right side), configure the following options:
   - #### Transform
     - Forward: `Z Forward`
     - Up: `-Y Up`
   - #### Geometry
     - Normals
     - Triangulated Mesh
     - Apply Modifiers
4. Export the file into the *assets* folder of the project directory.

📌 Note:
- The engine uses a default resolution of 400x200 pixels.
- For the mesh to display correctly, you may need to reduce the size of your terminal window.
## 📅 Future plans
I plan to further expand this project as a way to deepen my understanding of 3D graphics and to improve both my design and programming skills. My goal is to refine the existing codebase and implement the currently missing features.
