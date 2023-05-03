#version 330 core

out vec4 fFragColor;

uniform float r;
uniform float g;
uniform float b;

void main(void) {
    fFragColor = vec4(r, g, b, 1.0);
}