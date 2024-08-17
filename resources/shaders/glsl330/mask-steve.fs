#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform sampler2D mask;
uniform int frame;
uniform vec2 textureSize; // Add this uniform to pass texture dimensions

// Output fragment color
out vec4 finalColor;

void main()
{
    // Calculate rotation angle (in radians)
    float angle = radians(frame * 0.5); // Adjust speed as needed

    // Create rotation matrix
    mat2 rotationMatrix = mat2(
        cos(angle), -sin(angle),
        sin(angle), cos(angle)
    );

    // Calculate texture coordinates
    vec2 texCoord = fragTexCoord - 0.5; // Center the rotation
    texCoord = rotationMatrix * texCoord; // Apply rotation
    texCoord += 0.5; // Move back to original position

    // Implement seamless texture repetition
    texCoord = fract(texCoord);

    // Sample the texture with rotated coordinates
    vec4 texelColor = texture(texture0, texCoord);

    finalColor = texelColor;
}