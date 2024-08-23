#version 330

in vec2 fragTexCoord;
out vec4 fragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float seconds;

vec3 neonColor(vec3 baseColor, float intensity) {
    return baseColor * intensity + pow(baseColor, vec3(4.0)) * 0.5;
}

vec3 bloom(sampler2D tex, vec2 uv, float lod) {
    vec3 accumulator = vec3(0.0);
    const float BLUR_STEPS = 5.0;
    
    for (float i = 0.0; i < BLUR_STEPS; i++) {
        float angle = 2.0 * 3.14159 * i / BLUR_STEPS;
        vec2 offset = vec2(cos(angle), sin(angle)) * lod * 0.01;
        accumulator += texture(tex, uv + offset).rgb;
    }
    
    return accumulator / BLUR_STEPS;
}

void main()
{
    vec2 res = vec2(1280,720);
    vec2 uv = fragTexCoord;
    uv.x = fract(uv.x + seconds * 0.2);  // Horizontal movement with wrapping
    
    float grad = mix(0.0, 2.0, fragTexCoord.x - 0.35);
    
    // Sample distortion texture
    vec4 d = texture(texture1, fragTexCoord);
    
    // Use distortion for both noise distortion and lighting effect
    vec4 n = texture(texture0, uv.xy + d.rg * 0.1);
    n += grad;
    
    // Create base color
    vec3 baseColor = mix(vec3(0.0, 0.0, 1.0), vec3(0.0, 0.5, 0.5), fragTexCoord.x);
    
    // Use distortion texture for lighting effect
    float lightingIntensity = (d.r + d.g + d.b) / 3.0;
    lightingIntensity = pow(lightingIntensity, 2.0);  // Increase contrast
    
    // Combine neon color with lighting effect
    vec3 color = neonColor(baseColor, n.r * 2.0 + lightingIntensity);
    
    // Add bloom
    vec3 bloomColor = bloom(texture0, uv, 4.0);
    color += bloomColor * 0.5;  // Adjust bloom intensity
    
    // Add pulsating effect using distortion texture
    float pulse = sin(seconds * 2.0) * 0.5 + 0.5;
    color += lightingIntensity * pulse * baseColor * 0.5;
    
    // Enhance brightness
    color = pow(color, vec3(0.6));  // Gamma correction to brighten
    
    fragColor = vec4(color, 1.0);
}