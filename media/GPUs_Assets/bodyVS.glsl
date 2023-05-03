#version 330 core

in vec4 vertex;

uniform mat4 modelViewProjectionMatrix;

void main(void) {
    gl_Position = modelViewProjectionMatrix * vertex;
}