#include "raylib.h"
#include <math.h>
#include <stdio.h>

#define MAX_COLUMNS 20
#define WIDTH 800
#define HEIGHT 600
#define MOVEMENT_SPEED
#define INTENSITY 5.0f

float PerlinNoise3D(float x, float y, float z, float time) {
    // Use very high frequency for the x, y, z terms to generate tiny ripples
    //                    ripples        Intensity             frequency
    float noise = sinf(x * 10.0f + time * 5.0f) * 0.05f // High frequency for tiny ripples
                + sinf(y * 10.0f + time * 5.0f) * 0.05f  // Higher frequency and smaller intensity
                + sinf(z * 10.0f + time * 5.0f) * 0.05f; // Even higher frequency for finer detail
    return noise;
}

int main() {
    // Initialize our window and camera
    InitWindow(WIDTH, HEIGHT, "Audio Visualizer");

    Camera cam = {0};
    cam.position = (Vector3) {0.0f, 3.0f, 4.0f};
    cam.target = (Vector3) {0.0f, 0.0f, 0.0f};
    cam.up = (Vector3) {0.0f, 1.0f, 0.0f};
    cam.fovy = 45.0f;
    cam.projection = CAMERA_PERSPECTIVE;

    // Set our window to run at inf frames-per-second
    SetTargetFPS(-1);

    // Create a mesh (a list of vertices/points and faces that form triangles to make a geometric shape)
    Mesh sphereMesh = GenMeshSphere(1.0f, 96, 96);
    // Create a model using our sphere mesh
    Model sphere = LoadModelFromMesh(sphereMesh);

    // 
    float time = 0.0f;

    /** SPLIT INTO 3 PARTS
     * 1. Event Handling
     * 2. Updating Positions of game objects
     * 3. Drawing Objects (draw all objects in new positions)
     * !WindowShouldClose() Checks if the X button or esc is pressed
     */
    while (!WindowShouldClose()) {
        time += GetFrameTime();
        // 1. Event Handling

        // 2. Updating Positions of game objects
        UpdateCamera(&cam, CAMERA_ORBITAL);

        // Apply perlin Noise
        for (int i = 0; i < sphereMesh.vertexCount; i++) {
            float* vertices = sphereMesh.vertices;
            float x = vertices[i * 3 + 0];
            float y = vertices[i * 3 + 1];
            float z = vertices[i * 3 + 2];

            // Generate the noise value for this vertex
            float noise = PerlinNoise3D(x, y, z, time);

            // Decrease displacement to create smaller, lower-intensity ripples
            float displacement = (noise /*Variable here later*/) * 0.4f;  // Lower displacement for less intensity

            // Normalize the vertex direction to maintain spherical shape
            float distance = sqrtf(x * x + y * y + z * z);  // Calculate distance from origin
            float norm_x = x / distance;  // Normalize the vertex direction
            float norm_y = y / distance;
            float norm_z = z / distance;

            // Apply the displacement and keep the vertex on the sphere's surface
            vertices[i * 3 + 0] = (x + displacement * norm_x) / distance * 1.0f;
            vertices[i * 3 + 1] = (y + displacement * norm_y) / distance * 1.0f;
            vertices[i * 3 + 2] = (z + displacement * norm_z) / distance * 1.0f;
        }

        // Update the mesh with modified vertices
        UpdateMeshBuffer(sphereMesh, 0, sphereMesh.vertices, sphereMesh.vertexCount * 3 * sizeof(float), 0);
        
        // 3. Drawing Objects
        BeginDrawing(); // creates blank canvas so we can draw game object on
        // To handle updating draw calls, we must clear the window each iteration
        // so it doesn't repeatedly leave old draw call
        ClearBackground(WHITE);
        BeginMode3D(cam);

        // Draw our sphere model
        DrawModelWires(sphere, (Vector3) {0.0f, 0.0f, 0.0f}, 1.0f, BLACK);
        // DrawModel(sphere, (Vector3) {0.0f, 0.0f, 0.0f}, 1.0f, WHITE);

        EndMode3D();
        DrawFPS(10, 10);
        EndDrawing(); // End canvas drawing and swaps buffers
    }

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context

    return 0;
}