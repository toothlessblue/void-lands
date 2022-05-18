#version 300 es
precision mediump float;

layout(location = 0) in vec3 vertexPosition_modelspace;
uniform mat4 modelViewProjection;

void main() {
    gl_Position = modelViewProjection * vec4(vertexPosition_modelspace, 1);
}