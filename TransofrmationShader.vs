#version 400 

uniform mat4 transformation = mat4(1);
uniform mat4 viewMatrix = mat4(1); // bug in perspective FOv matrix
uniform mat4 projection = mat4(1);
uniform mat4 scale = mat4(1);
uniform vec3 LightSource ;
uniform float IsTexture ;

varying vec3 outColor; 
varying vec2 outTexCoord;
varying vec3 outLightSource ;
varying vec3 outNormal ;
varying float outIsTexture ;

attribute vec3 inVertex;
attribute vec3 inColor ;// values in vertex 
attribute vec2 inTexCoord;
attribute vec3 inNormal;



void main()
{
//gl_ModelViewProjectionMatrix*
		vec4 vertex = vec4(inVertex,1) * scale ;
		mat4 LviewMatrix = gl_ModelViewProjectionMatrix;
		if (viewMatrix != mat4(1))
		LviewMatrix = viewMatrix ;
		
	  gl_Position = projection * viewMatrix * transformation * vertex;
	//	gl_Position= gl_ModelViewProjectionMatrix * transformation * vertex;
		 
		
		outNormal.xyz = normalize(vec4(inNormal,1) * transformation);
		outLightSource = LightSource ;
		
		outIsTexture = IsTexture ;
		outTexCoord = inTexCoord ;
		outColor=inColor;
		
}