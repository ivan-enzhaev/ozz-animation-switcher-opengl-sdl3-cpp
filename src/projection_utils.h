#pragma once

#include "app.h"
#include <SDL3/SDL.h>
#include <cglm/cglm.h>

inline void updateProjectionAndMVP(App *app)
{
    int windowW, windowH;
    SDL_GetWindowSizeInPixels(app->window, &windowW, &windowH);

    // Update OpenGL viewport to match the new pixel dimensions
    glViewport(0, 0, windowW, windowH);

    float windowAspect = (float)windowW / (float)windowH;

    mat4 projMatrix;

    // Instead of a hardcoded fixed vertical size, check orientation
    // or base the frustum bounds on the text's actual dimensions to prevent clipping
    float orthoSize = 300.0f;

    float left, right, bottom, top;

    if (windowW >= windowH)
    {
        // Landscape mode: fix vertical height, scale width by aspect ratio
        left = -orthoSize * windowAspect;
        right = orthoSize * windowAspect;
        bottom = -orthoSize;
        top = orthoSize;
    }
    else
    {
        // Portrait mode: fix horizontal width, scale height by inverse aspect ratio
        left = -orthoSize;
        right = orthoSize;
        bottom = -orthoSize / windowAspect;
        top = orthoSize / windowAspect;
    }

    glm_ortho(left, right, bottom, top, -1.0f, 1.0f, projMatrix);

    mat4 viewMatrix;
    vec3 eye = { 0.0f, 0.0f, 1.0f };
    vec3 center = { 0.0f, 0.0f, 0.0f };
    vec3 up = { 0.0f, 1.0f, 0.0f };
    glm_lookat(eye, center, up, viewMatrix);

    glm_mat4_mul(projMatrix, viewMatrix, app->projView2D);
}

inline void update3DProjectionAndMVP(App *app)
{
    int windowW, windowH;
    SDL_GetWindowSizeInPixels(app->window, &windowW, &windowH);
    if (windowH == 0)
        windowH = 1; // Prevent division by zero

    float windowAspect = (float)windowW / (float)windowH;

    // Perspective Projection for 3D
    mat4 projMatrix;
    glm_perspective(glm_rad(45.0f), windowAspect, 2.0f, 1000.0f, projMatrix);

    // Camera View Matrix (positioned at eys, looking at center)
    mat4 viewMatrix;
    vec3 eye = { 1.0f, 3.0f, 13.0f };
    vec3 center = { 0.0f, 3.0f, 0.0f };
    vec3 up = { 0.0f, 1.0f, 0.0f };
    glm_lookat(eye, center, up, viewMatrix);

    // Optional: Rotate the cube slightly or based on time/animation
    // glm_rotate(app->cubeModelMatrix, app->cubeRotationAngle, (vec3){ 1.0f, 1.0f, 0.0f });

    // Combine into MVP: MVP = Projection * View * Model
    glm_mat4_mul(projMatrix, viewMatrix, app->projView3D);
}
