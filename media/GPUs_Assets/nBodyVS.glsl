#version 330 core

in vec4 vertex;

uniform mat4 modelViewProjectionMatrix;
uniform float time;
uniform float mass;
uniform float radius;
uniform float speed;

void main(void) {
    vec4 transformedPosition = modelViewProjectionMatrix * vertex;
    
    //Posición calculada correctamente
    //float G = 6.6743e-11; // Constante gravitatoria de Newton
    //float M = 1.9891e30; 

    //float E_cin = 0.5 * mass * pow(radius, 2); // Energía cinética inicial
    //float v0 = sqrt(2 * E_cin / mass); // Velocidad inicial

    //float F = (G * mass * M) / pow(radius, 2); // Fuerza gravitatoria
    //float a = F / mass; // Aceleración

    //float x = radius * cos(v0 / radius * time); // Posición en el eje x
    //float y = radius * sin(v0 / radius * time); // Posición en el eje y

    //Simulación bonita
    float x = radius * cos(time * speed);
    float y = radius * sin(time * speed);

    transformedPosition.x += x;
    transformedPosition.y += y;

    gl_Position = transformedPosition;
}
