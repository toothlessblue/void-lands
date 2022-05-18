#version 300 es
precision highp float;

uniform vec3 inColour;
out vec4 colour;

void main() {
    colour = vec4(inColour, 1.0f);
}