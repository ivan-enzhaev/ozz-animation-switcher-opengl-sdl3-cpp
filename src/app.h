#pragma once

#include <cglm/cglm.h>
#include <vector>

struct Mat4Wrapper
{
    mat4 m;
};

typedef struct
{
    SDL_Window *window;
    SDL_GLContext glContext;
    GLuint shaderProgram;
    GLuint vao, vbo;
    GLuint textTextureID;
    TTF_Font *font;
    int textW;
    int textH;
    mat4 mvpMatrix;
    GLint uMvpMatrixLocation;
    ImGuiIO *io;
    float scale_factor;
    GLuint cubeVao, cubeVbo, cubeUvVbo, cubeEbo;
    GLsizei cubeIndexCount;
    GLenum cubeIndexType;
    mat4 projView2D;
    mat4 projView3D;
    float cubeRotationAngle;
    GLuint cubeTextureID;
    // Ozz-animation fields
    ozz::animation::Skeleton ozzSkeleton;
    ozz::animation::Animation ozzIdleAnimation;
    ozz::animation::Animation ozzWalkAnimation;
    ozz::animation::Animation ozzRunAnimation;
    ozz::animation::SamplingJob::Context ozzSamplingContext;
    float ozzAnimationTime;
    ozz::vector<ozz::math::Float4x4> ozzModelMatrices;
    GLuint lineShaderProgram;
    GLint uLineMvpMatrixLocation;
    GLint uLineColorLocation;
    GLuint lineVao, lineVbo;
    // Skinning Fields
    GLuint skinningShaderProgram;
    GLint uSkinningMvpMatrixLocation;
    GLint uJointMatricesLocation;
    GLuint ybotVao;
    GLuint ybotVbo;       // Positions
    GLuint ybotUvVbo;     // UVs
    GLuint ybotJointVbo;  // Joint Indices (ivec4)
    GLuint ybotWeightVbo; // Joint Weights (vec4)
    GLuint ybotEbo;       // Indices
    GLsizei ybotIndexCount;
    GLenum ybotIndexType;
    GLuint ybotTextureID;
    std::vector<Mat4Wrapper> ybotInverseBindMatrices;
    bool showDebugSkeleton;
    bool showRobot;
} App;
