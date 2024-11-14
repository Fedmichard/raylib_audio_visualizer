#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tinyfiledialogs.h"
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define MAX_COLUMNS 20
#define WIDTH 800
#define HEIGHT 600

// Noise Variables
float ripples = 12.0f; // Amount of ripples
float intensity = 8.0f; // amplitude or the height of the wave from its center
float frequency = 0.025f; // how many cycles the wave completes within a certain interval
float multiplier = 1.0f; // our noise multipler

// Audio Processing Variables
static float exponent = 1.0f; // Audio exponentiation value
static float averageVolume[400] = { 0.0f }; // buffer to store Average volume history
char* song = "../resources/The Dread.mp3"; // set to a default song in resources file

// Color picker
float r = 255;
float g = 255;
float b = 255;

/**
 * function that takes in an x, y, z value of a point on our sphere mesh
 * takes a time value to animate our point over time
 * sinf produces a wave-like variations 
 */
float noise3D(float x, float y, float z, float time) {
    // Use very high frequency for the x, y, z terms to generate tiny ripples
    //                    ripples       Intensity frequency
    float noise = sinf(x * ripples + time * intensity) * frequency // High frequency for tiny ripples
                + sinf(y * ripples + time * intensity) * (frequency)  // Higher frequency and smaller intensity
                + sinf(z * ripples + time * intensity) * (frequency); // Even higher frequency for finer detail
    return noise;
}

/**
 * Attaching to our entire audio pipeline, receives the samples as floats
 * samples: a single point of audio data. A snapshot of the amplitude of some audio signal
 *          when audio is recorded, it is captured many thousands of times per sec
 *          each of these are samples. 44.1 kHz, 44,100 samples per second
 * sample rate: how many samples are captured per second, the higher the sample rate the more
 *              audio can be processed directly to digital with more precision and quality.
 * buffer: temporary storage area to hold data while it's being transferred or processed, in this
 *         situation it's a spot that audio data (samples) 
 * frame: a group of all samples that happened in that frame, in our example it's
 */
void processAudio(void *buffer, unsigned int frames) {
    float *samples = (float *)buffer;   // Samples internally stored as <float>s
    float average = 0.0f;               // Temporary average volume

    for (unsigned int frame = 0; frame < frames; frame++) {
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
    AttachAudioMixedProcessor(processAudio); // Attaches an audio processor to and returns fkiats
    // load music and play it
    Music music = LoadMusicStream(song);
    // PlayMusicStream(music);
    // Set our window to run at inf frames-per-second
    SetTargetFPS(-1);

    // Create a mesh (a list of vertices/points and faces that form triangles to make a geometric shape)
    Mesh sphereMesh = GenMeshSphere(1.0f, 48, 96);
    // Create a model using our sphere mesh
    Model sphere = LoadModelFromMesh(sphereMesh);

    // time value of our workspace
    float time = 0.0f;

    bool showSuccess = false;
    bool showFail = false;

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
        // Apply Noise
        for (int i = 0; i < sphereMesh.vertexCount; i++) {
            float* vertices = sphereMesh.vertices;
            float x = vertices[i * 3 + 0];
            float y = vertices[i * 3 + 1];
            float z = vertices[i * 3 + 2];

            // Generate the noise value for this vertex
            float noise = noise3D(x, y, z, time);

            // Decrease displacement to create smaller, lower-intensity ripples
            float displacement = noise * multiplier;  // Lower displacement for less intensity

            // Normalize the vertex direction to maintain spherical shape
            float distance = sqrtf(x * x + y * y + z * z);  // Calculate distance from origin
            float norm_x = x / distance;  // Normalize the vertex direction
            float norm_y = y / distance;
            float norm_z = z / distance;

            // Apply the displacement and keep the vertex on the sphere's surface
            // distance maintains it's maximum outwards distance, keeps it from moving off screen
            vertices[i * 3 + 0] = (x + displacement * norm_x) / distance * 1.0f;
            vertices[i * 3 + 1] = (y + displacement * norm_y) / distance * 1.0;
            vertices[i * 3 + 2] = (z + displacement * norm_z) / distance * 1.0;
        }
        // Adjust noise multiplier based on volume
        for (int i = 0; i < 400; i++)
        {
            multiplier = (averageVolume[i] * 7) + 0.1f;
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
                DrawModelWires(sphere, (Vector3) {0.0f, 0.0f, 0.0f}, 1.0f, (Color){r, g, b, 255});
            EndMode3D();

            /**
            * GUI SECTION; After 3D mode but before ending draw, so gui overlays on top
            */

            // Music status variables
            GuiPanel((Rectangle){675, 100, 100, 25}, "     Default."); // default song

            if (showSuccess) {
                int success = GuiPanel((Rectangle){675, 100, 100, 25}, "    Success!"); // successfully uploaded
            }
            if (showFail) {
                int fail = GuiPanel((Rectangle){675, 100, 100, 25}, "      Failed."); // failed to uploaded
            }

            if (GuiButton((Rectangle){675, 25, 100, 50}, "Upload")) {
                void* org = song;
                song = tinyfd_openFileDialog("Explorer", "", 0, (const char*[])
                                            {"*.wav", "*.mp3", "*.ogg"}, "Audio Files", 0);
                // if no song was loaded in
                if (!song) {song = org;}
                music = LoadMusicStream(song);

                if (IsMusicReady(music)) {
                    showFail = false;
                    showSuccess = true;
                } else {
                    showSuccess = false;
                    showFail = true;
                }
            }

            // Music Interaction Portion
            if (GuiButton((Rectangle){675, 75, 50, 25}, "Play")) {
                PlayMusicStream(music);
            }

            if (GuiButton((Rectangle){725, 75, 50, 25}, "Stop")) {
                PauseMusicStream(music);
            }

            GuiSliderBar((Rectangle){675, 125, 100, 25}, "Level", "", &multiplier, 0.0f, 2.5f);

            // Color Picker Portion
            GuiSlider((Rectangle){675, 150, 100, 10}, "R", "", &r, 0, 255);
            GuiSlider((Rectangle){675, 160, 100, 10}, "G", "", &g, 0, 255);
            GuiSlider((Rectangle){675, 170, 100, 10}, "B", "", &b, 0, 255);

            // FPS Counter
            // DrawFPS(10, 10);
        EndDrawing(); // End canvas drawing and swaps buffers
    }

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context

    return 0;
}