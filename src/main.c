#include "raylib.h"
#include <math.h>
#include <stdio.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define MAX_COLUMNS 20
#define WIDTH 800
#define HEIGHT 600
#define MOVEMENT_SPEED
#define INTENSITY 5.0f

float ripples = 12.0f;
float intensity = 8.0f;
float frequency = 0.025f;
float num = 0.4f;

static float exponent = 1.0f; // Audio exponentiation value
static float averageVolume[400] = { 0.0f }; // Average volume history

float perlinNoise3D(float x, float y, float z, float time) {
    // Use very high frequency for the x, y, z terms to generate tiny ripples
    //                    ripples       Intensity frequency
    float noise = sinf(x * ripples + time * intensity) * frequency // High frequency for tiny ripples
                + sinf(y * ripples + time * intensity) * frequency  // Higher frequency and smaller intensity
                + sinf(z * ripples + time * intensity) * frequency; // Even higher frequency for finer detail
    return noise;
}

void ProcessAudio(void *buffer, unsigned int frames)
{
    float *samples = (float *)buffer;   // Samples internally stored as <float>s
    float average = 0.0f;               // Temporary average volume

    for (unsigned int frame = 0; frame < frames; frame++)
    {
        float *left = &samples[frame * 2 + 0], *right = &samples[frame * 2 + 1];

        *left = powf(fabsf(*left), exponent) * ( (*left < 0.0f)? -1.0f : 1.0f );
        *right = powf(fabsf(*right), exponent) * ( (*right < 0.0f)? -1.0f : 1.0f );

        average += fabsf(*left) / frames;   // accumulating average volume
        average += fabsf(*right) / frames;
    }

    // Moving history to the left
    for (int i = 0; i < 399; i++) averageVolume[i] = averageVolume[i + 1];

    averageVolume[399] = average;         // Adding last average value
}

int main() {
    // Initialize our window
    InitWindow(WIDTH, HEIGHT, "Audio Visualizer");

    // Initialize our camera
    Camera cam = {0};
    cam.position = (Vector3) {0.0f, 3.0f, 4.0f};
    cam.target = (Vector3) {0.0f, 0.0f, 0.0f};
    cam.up = (Vector3) {0.0f, 1.0f, 0.0f};
    cam.fovy = 45.0f;
    cam.projection = CAMERA_PERSPECTIVE;

    // Initialize our audio system
    InitAudioDevice();
    AttachAudioMixedProcessor(ProcessAudio);
    Music music = LoadMusicStream("../resources/yt5s.com - Ghostpocalypse (Action Music) - Vanoss Gaming Background Music (HD) (128 kbps) (1).mp3");
    PlayMusicStream(music);
    // Set our window to run at inf frames-per-second
    SetTargetFPS(-1);

    // Create a mesh (a list of vertices/points and faces that form triangles to make a geometric shape)
    Mesh sphereMesh = GenMeshSphere(1.0f, 48, 96);
    // Create a model using our sphere mesh
    Model sphere = LoadModelFromMesh(sphereMesh);

    // time value of our workspace
    float time = 0.0f;

    /** SPLIT INTO 3 PARTS
     * 1. Event Handling
     * 2. Updating Positions of game objects
     * 3. Drawing Objects (draw all objects in new positions)
     * !WindowShouldClose() Checks if the X button or esc is pressed
     */
    while (!WindowShouldClose()) {
        time += GetFrameTime();
        UpdateMusicStream(music);
        float playTime = GetMusicTimePlayed(music);
        float musicLength = GetMusicTimeLength(music);

        // 1. Event Handling / input handline
        /**
         * NONE
         */

        // 2. Updating Positions of game objects
        UpdateCamera(&cam, CAMERA_ORBITAL);
        // Apply perlin Noise
        for (int i = 0; i < sphereMesh.vertexCount; i++) {
            float* vertices = sphereMesh.vertices;
            float x = vertices[i * 3 + 0];
            float y = vertices[i * 3 + 1];
            float z = vertices[i * 3 + 2];

            // Generate the noise value for this vertex
            float noise = perlinNoise3D(x, y, z, time);

            // Decrease displacement to create smaller, lower-intensity ripples
            float displacement = (noise) * num;  // Lower displacement for less intensity

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


        for (int i = 0; i < 400; i++)
        {
            num = (averageVolume[i] * 5) + 0.1f;
        }

        // Update the mesh with modified vertices
        UpdateMeshBuffer(sphereMesh, 0, sphereMesh.vertices, sphereMesh.vertexCount * 3 * sizeof(float), 0);
        
        // 3. Drawing Objects
        BeginDrawing(); // creates blank canvas so we can draw game object on
            // To handle updating draw calls, we must clear the window each iteration
            // so it doesn't repeatedly leave old draw call
            ClearBackground(BLACK);

            // begin 3D space
            BeginMode3D(cam);
                // Draw our sphere model
                DrawModelWires(sphere, (Vector3) {0.0f, 0.0f, 0.0f}, 1.0f, GREEN);
            EndMode3D();

            // GUI
            if (GuiButton((Rectangle){675, 25, 100, 50}, "Upload")) {

            }

            if (GuiButton((Rectangle){675, 75, 50, 25}, "Play")) {
                PlayMusicStream(music);
                num = (sinf(playTime * 10.0f) + 1.0f) * 1.25f;
            }

            if (GuiButton((Rectangle){725, 75, 50, 25}, "Stop")) {
                PauseMusicStream(music);
            }
            if (GuiSliderBar((Rectangle){675, 125, 100, 25}, "Effect", "#", &num, 0.0f, 2.5f)) {

            }
            
            // FPS Counter
            DrawFPS(10, 10);
        EndDrawing(); // End canvas drawing and swaps buffers
    }

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context

    return 0;
}