#version 300 es
precision highp float;

uniform sampler2D textureSampler;
in vec2 uv;

out vec4 colour;

void main() {
    colour = texture(textureSampler, uv).rgba;
}