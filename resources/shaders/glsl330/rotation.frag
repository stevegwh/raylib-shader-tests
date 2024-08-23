// // Fragment Shader
// #version 330

// in vec2 fragTexCoord;
// in vec3 fragNormal;

// out vec4 fragColor;

// uniform sampler2D texture0;
// uniform sampler2D texture1;
// uniform float seconds;


// // https://iquilezles.org/articles/palettes
// vec3 palette(float t, vec3 a, vec3 b, vec3 c, vec3 d){ return a + b*cos( 6.28318*(c*t+d) ); }

// const float ColorAnchor[3]	= float[]( 0.0, 0.5, 0.75 );
// const vec4 ColorRamp[3]		= vec4[]( 
//     vec4(0.0,0.0,0.0,0.0),
//     vec4(0.933, 0.679, 0.378, 1.0),
//     vec4(1.0, 0.992, 0.703, 1.0)
// );

// vec4 getColorRamp(float v, float feather){
//     for(int i=0; i < 2; i++){
//         if(v >= ColorAnchor[i] && v < ColorAnchor[i+1])
//             return mix( ColorRamp[i], ColorRamp[i+1], smoothstep(ColorAnchor[i+1]-feather,ColorAnchor[i+1],v) );
//     }
//     return ColorRamp[2];
// }

// // Following the tutorial by SketchpunkLabs from: https://www.youtube.com/watch?v=uT5w3Bwhk4s
// void main()
// {
//     vec2 res = vec2(1280,720);
//     // Normalized pixel coordinates (from 0 to 1)
//     vec2 uv = fragTexCoord;
//     uv.y += seconds * 0.2;

//     float grad = mix(0.0, 2.0, fragTexCoord.y - 0.45);
//     // fragColor = vec4(grad,grad,grad,1);
//     // return;

//     vec4 d = texture(texture1, fragTexCoord) * 0.1;
//     vec4 n = texture(texture0, uv.xy + d.rg);
//     n += grad;
    
//     // Normal color gradient
//     // fragColor = vec4(n.r, n.r, n.r, 1);
//     // fragColor *= mix( vec4(1.0, 1.0, 0.0, 1.0), vec4(1.0, 0.0, 0.0, 1.0), fragTexCoord.y );

//     // Hard mask
//     //float nn = step(0.5, n.r);
    
//     // Soft mask
//     // float nn = smoothstep(0.5, 0.65, n.r);
//     // fragColor = vec4(nn, nn, nn, 1);

//     fragColor = getColorRamp( clamp(n.r, 0.0, 1.0), 0.05 );
// }

// // Portal looking thing
// // // Following the tutorial by SketchpunkLabs from: https://www.youtube.com/watch?v=uT5w3Bwhk4s
// // void main()
// // {
// //     vec2 res = vec2(1280,720);
// //     // Normalized pixel coordinates (from 0 to 1)
// //     vec2 uv = fragTexCoord;
// //     uv.y += seconds * 0.2;

// //     vec4 d = texture(texture1, fragTexCoord) * 0.5;

// //     vec4 n = texture(texture0, uv + d.rg);

// //     // vec2 uv2 = fragTexCoord;
// //     // uv2.xy += cos(seconds*10)/25;
// //     // vec4 color2 = texture(texture1, uv2);
// //     // color2.a = 0.8;


    
// //     fragColor = vec4(n.r, n.r, n.r, 1);
// // }


#version 330
in vec2 fragTexCoord;
in vec3 fragNormal;
out vec4 fragColor;
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float seconds;

// https://iquilezles.org/articles/palettes
vec3 palette(float t, vec3 a, vec3 b, vec3 c, vec3 d){ return a + b*cos( 6.28318*(c*t+d) ); }

const float ColorAnchor[3]  = float[]( 0.0, 0.5, 0.75 );
const vec4 ColorRamp[3]     = vec4[](
    vec4(0.0,0.0,0.0,0.0),
    vec4(0.933, 0.679, 0.378, 1.0),
    vec4(1.0, 0.992, 0.703, 1.0)
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
    
    // Change vertical movement to horizontal
    uv.x += seconds * 0.2;
    
    // Change gradient direction from vertical to horizontal
    float grad = mix(0.0, 2.0, fragTexCoord.x - 0.45);
    
    vec4 d = texture(texture1, fragTexCoord) * 0.1;
    vec4 n = texture(texture0, uv.xy + d.rg);
    n += grad;
   
    fragColor = getColorRamp( clamp(n.r, 0.0, 1.0), 0.05 );
}