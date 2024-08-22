// Fragment Shader
#version 330

in vec2 fragTexCoord;
in vec3 fragNormal;

out vec4 fragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float seconds;


// https://iquilezles.org/articles/palettes
vec3 palette(float t, vec3 a, vec3 b, vec3 c, vec3 d){ return a + b*cos( 6.28318*(c*t+d) ); }

const float ColorAnchor[3]	= float[]( 0.0, 0.5, 0.75 );
const vec4 ColorRamp[3]		= vec4[]( 
    vec4(0.0,0.0,0.0,0.0),
    vec4(219./255.,56./255.,201./255.,1.0),
    vec4(160./255.,246./255.,180./255.,1.0)
);

vec4 getColorRamp(float v, float feather){
    for(int i=0; i < 2; i++){
        if(v >= ColorAnchor[i] && v < ColorAnchor[i+1])
            return mix( ColorRamp[i], ColorRamp[i+1], smoothstep(ColorAnchor[i+1]-feather,ColorAnchor[i+1],v) );
    }
    return ColorRamp[2];
}

// Following the tutorial by SketchpunkLabs from: https://www.youtube.com/watch?v=uT5w3Bwhk4s
void main()
{
    vec2 res = vec2(1280,720);
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = fragTexCoord;
    uv.y += seconds * 0.2;

    vec4 d = texture(texture1, fragTexCoord) * 0.5;

    vec4 n = texture(texture0, uv + d.rg);

    // vec2 uv2 = fragTexCoord;
    // uv2.xy += cos(seconds*10)/25;
    // vec4 color2 = texture(texture1, uv2);
    // color2.a = 0.8;


    
    fragColor = vec4(n.r, n.r, n.r, 1);
}