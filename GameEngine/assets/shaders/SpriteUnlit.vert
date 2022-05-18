#version 300 es
precision mediump float;

layout(location = 0) in vec3 vertices;
layout(location = 1) in vec2 vertexUV;

uniform mat4 modelViewProjection;

out vec2 uv;

void main() {
    gl_Position = modelViewProjection * vec4(vertices, 1);
    uv = vertexUV;
}