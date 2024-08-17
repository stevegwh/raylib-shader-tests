#version 300 es
	//precision highp float;
	layout(location=0) in vec4 a_position;
	layout(location=1) in vec3 a_normal;
	layout(location=2) in vec2 a_uv;

	uniform UBOTransform{
		mat4 matProjection;
		mat4 matCameraView;
		vec3 posCamera;
		float fTime;
	};

	uniform mat4 uModalMatrix;
	uniform mat3 uNormalMatrix;

	out vec3 oColor;
	out vec3 oNorm;
	out float vDotFromCamera;
	out vec2 v_uv;
	out vec2 v_uv2;
	flat out float v_time;

	void main(void){
		//..............................
		//Calc World Space for Vertex & Rotate Normals to be pointing in correct direction.
		vec4 worldPos	= uModalMatrix * vec4(a_position.xyz,1.0);
		vec3 worldNorm	= normalize(uNormalMatrix * a_normal);

		//..............................
		// FRESNEL
		// Angle difference between vertex's normal direction and the vertex's camera direction
		vec3 dirToCamera = normalize(posCamera - worldPos.xyz);
		vDotFromCamera = dot(worldNorm,dirToCamera);

		//..............................
		//gl_Position	= matProjection * matCameraView * uModalMatrix * vec4(a_position.xyz,1.0);
		gl_Position	= matProjection * matCameraView * worldPos;


		//..............................
		v_time = fTime;

		//..............................
		v_uv = a_uv;
		v_uv.x += fTime * 0.0001;
		v_uv.y += fTime * 0.0006;

		//..............................
		v_uv2 = a_uv;
		v_uv2.x = clamp(fract(fTime * 0.0003),0.0,1.0);
		//v_uv2.x = clamp(fract(0.0002),0.0,1.0);
	}