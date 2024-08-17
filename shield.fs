#version 300 es
	precision highp float;

	flat in float v_time;
	
	in vec3 oNorm;
	in vec2 v_uv;
	in vec2 v_uv2;
	in float vDotFromCamera;
	
	uniform sampler2D bufColor;
	uniform sampler2D bufDepth;
	uniform sampler2D u_tex01;

	out vec4 outColor;

	//===================================
	const float PROJ_NEAR = 0.1; //This can also be uniforms or part of a UBO.
	const float PROJ_FAR = 100.0;	

	float mapDepthToProj(float depth){ //depth is should be between 0:1
		float ndc = 2.0 * depth - 1.0;  //Normalized Device Space -1:1
		return -(2.0 * PROJ_FAR * PROJ_NEAR) / (ndc * (PROJ_FAR - PROJ_NEAR) - PROJ_FAR - PROJ_NEAR);
	}

	//===================================
	//Should be uniforms down the line.
	const vec4 baseColor = vec4(0.0,0.9,0.0,0.1);
	const vec4 rimColor = vec4(0.0,1.0,0.0,1.0);


	void main(void){
		//-----------------------------
		// Get Depth and exit out if current pixel Z is greater then whats in the depth buffer.
		// exit if current fragment is further away from camera then depth tex fragment
		ivec2 fCoord	= ivec2(gl_FragCoord.xy);
		float zTexDepth	= texelFetch(bufDepth, fCoord , 0).x;

		if(gl_FragCoord.z > zTexDepth) discard;

		//-----------------------------
		/* Our texture should be a mask texture */
		vec4 maskA = texture(u_tex01,v_uv);
		maskA.a = maskA.r; //We're doing lots alpha blending, so need to set alpha on things.
		//outColor = maskA;

		//-----------------------------
		/* base on mask, distort on the x texture position */
		float distortStrength = 20.0;
		fCoord.x += int( (maskA.x * 2.0 - 1.0)  * distortStrength ); 
		vec4 distort = texelFetch(bufColor, fCoord, 0);
		//outColor = distort;

		//-----------------------------
		/* Combined our distortion and colored mask texture */
		outColor = distort * (maskA.a) + maskA * baseColor;
		//outColor = maskA * baseColor; //no distortion

		//-----------------------------
		/* Add fresnel */
		float fresnelMin = 0.05;
		float fresnelMax = 0.6;
		if(vDotFromCamera >= 0.0 && vDotFromCamera <= fresnelMax){
			outColor += rimColor * (1.0 - smoothstep(fresnelMin,1.0, (vDotFromCamera/fresnelMax) ));
		}

		//-----------------------------
		/* Add Intersection */
		float zPixelTex		= mapDepthToProj(zTexDepth);		//Pixel Depth from Texture
		float zPixelFrag	= mapDepthToProj(gl_FragCoord.z);	//Pixel Depth of current rendering fragment
		float zDelta		= abs(zPixelTex - zPixelFrag);		//Difference between the two

		float intersectMin	= 0.0;
		float intersectMax	= 0.15;
		if(zDelta <= intersectMax){
			outColor += rimColor * max(1.0 - zDelta / intersectMax, intersectMin );
		}

		//-----------------------------
		/* Add Highlights from the mask */

		//float hTime = 2.0 * abs(sin(v_time * 0.0007)) - 1.0 ; // -1:1 to 0:1
		//float highliteMin = (0.9 * hTime * hTime);
		float highliteMin = 0.9;
		outColor += smoothstep(highliteMin,1.0,maskA.r) * vec4(1.0,1.0,1.0,1.0);


		//-----------------------------
		/* Add one more mask at the end for fun */
		vec4 maskB = texture(u_tex01,v_uv2);
		outColor += maskB * maskB.r * 0.8;
	}