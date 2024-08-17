#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Output fragment color
out vec4 finalColor;

// Custom variables
uniform float seconds;
uniform vec2 size;

// NOTE: Render size values should be passed from code
const float renderWidth = 800;
const float renderHeight = 450;

vec3 palette(float t) {
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1.0, 1.0, 1.0);
    vec3 d = vec3(0.263, 0.416, 0.557);
    return a + b*cos(6.28318*(c*t + d));
}

void main() {
    vec2 uv = fragTexCoord*2.0 - 1.0;
    uv.x *= renderWidth/renderHeight;
    vec2 uv0 = uv;
    vec3 tmpColor = vec3(0.0);
    for (float i = 0.0; i < 4.0; i++) {
        uv = fract(uv*1.5) - 0.5;
        float d = length(uv)*exp(-length(uv0));
        vec3 col = palette(length(uv0) + i*0.4 + seconds*0.4);
        d = sin(d*8.0 + seconds)/8.0;
        d = abs(d);
        d = pow(0.01/d, 1.2);
        tmpColor += col*d;
    }
    finalColor = vec4(tmpColor, 1.0);
}