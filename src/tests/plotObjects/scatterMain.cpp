#include <iostream>
#include <tuple>
#include <chrono>
#include "raylib.h"
#include "rcamera.h"
#include "../../plotObjects/scatterBackend.h"
#include "../../plotObjects/gridLines3D.h"

#include "extensionsVector3.h"

#define numPoints   8


void drawTextAnnotations(const Camera &camera, const CameraMode &cameraMode) {
    DrawText("Camera status:", 610, 15, 10, BLACK);
    DrawText(TextFormat("- Mode: %s", (cameraMode == CAMERA_FREE) ? "FREE" :
                                      (cameraMode == CAMERA_FIRST_PERSON) ? "FIRST_PERSON" :
                                      (cameraMode == CAMERA_THIRD_PERSON) ? "THIRD_PERSON" :
                                      (cameraMode == CAMERA_ORBITAL) ? "ORBITAL" : "CUSTOM"), 610, 30, 10, BLACK);
    DrawText(TextFormat("- Projection: %s", (camera.projection == CAMERA_PERSPECTIVE) ? "PERSPECTIVE" :
                                            (camera.projection == CAMERA_ORTHOGRAPHIC) ? "ORTHOGRAPHIC" : "CUSTOM"), 610, 45, 10, BLACK);
    DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", camera.position.x, camera.position.y, camera.position.z), 610, 60, 10, BLACK);
    DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", camera.target.x, camera.target.y, camera.target.z), 610, 75, 10, BLACK);
    DrawText(TextFormat("- Up: (%06.3f, %06.3f, %06.3f)", camera.up.x, camera.up.y, camera.up.z), 610, 90, 10, BLACK);

}


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Scatter3d example");

    // Create the scatter object without actually plotting anything yet.
    std::vector<Vector3> data;
    std::vector<Color> colors;

    float ps[numPoints][3] = {  {-1, -1, -1},
                                {-1, -1, +1},
                                {-1, +1, -1},
                                {-1, +1, +1},
                                {+1, -1, -1},
                                {+1, -1, +1},
                                {+1, +1, -1},
                                {+1, +1, +1}};
    Color cs[numPoints] = {BLUE,
                            RED,
                            GREEN,
                            BLACK,
                            MAROON,
                            YELLOW,
                            PURPLE,
                            PINK};


    for (int i = 0; i < numPoints; ++i) {


        Vector3 newPoint{ps[i][0], ps[i][1], ps[i][2]};
        Color newColor = cs[i];

        data.push_back(newPoint);
        colors.push_back(newColor);
    }

    plotObjects::scatterBackend s{};
    s.setData(data);
    s.setColor(colors);
    s.setMarkerSize(0.3f);

    plotObjects::scatterBackend t;
    t.setMarkerSize(0.1f);

    std::vector<plotObjects::common3D*> plotElements3D;
    plotElements3D.push_back(&s);
    plotElements3D.push_back(&t);

    auto [minCorner, maxCorner] = plotObjects::getMostExtremeExtents(plotElements3D);
    plotObjects::gridLines3D g{};
    g.setExtents(minCorner, maxCorner);
    int numGridLines = 5;
    g.setNumLines(numGridLines);


    // Camera set up
    Camera camera = {0};
    camera.position = (Vector3){ 0.0f, 0.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_ORTHOGRAPHIC;

    CameraMode cameraMode = CAMERA_THIRD_PERSON;


    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------


    // Log start time
    auto t0 = std::chrono::high_resolution_clock::now();
    float waitTime = 1.0;
    float waitInc = 10.0f;

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Player movement

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                UpdateCamera(&camera, cameraMode);

                // Get the current elapsed time.
                auto t1 = std::chrono::high_resolution_clock::now();
                auto dt = t1 - t0;
                auto dt_sec = duration_cast<std::chrono::seconds>(dt);
                if (dt_sec.count() > waitTime) {
                    // Register a new point on a helix if the wait time has elapsed.
                    auto angle = static_cast<float>(waitTime) * 0.2;
                    auto x = angle * cosf(angle);
                    auto y = angle * sinf(angle);

                    s.addPoint({static_cast<float>(x), static_cast<float>(y), 0}, BLACK);
                    waitTime = waitTime + waitInc;
                    g.setNumLines(++numGridLines);
                }

                // Pulse the center scatter marker
                t.setMarkerSize(1.0f * sinf(0.001f * static_cast<float>(clock())));

                // Use std::tie to reuse the variables from the previous structured binding.
                std::tie(minCorner, maxCorner) = plotObjects::getMostExtremeExtents(plotElements3D);
                g.setExtents(minCorner, maxCorner);
                g.computeActiveGridPlanes(camera.position, camera.position - camera.target);
                g.setNumLines(numGridLines);


                // Loop through the elements and call .plot()
                for (auto &element : plotElements3D) {
                    element->plot();
                }
                g.plot();


            EndMode3D();

        DrawFPS(10, 10);
        drawTextAnnotations(camera, cameraMode);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}