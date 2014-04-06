#version 400 

uniform mat4 transformation = mat4(1);
uniform mat4 viewMatrix = mat4(1); // bug in perspective FOv matrix
uniform mat4 scale = mat4(1);

varying vec3 color2; 
varying vec2 texCoord;

attribute vec3 inVertex;
attribute vec3 inColor ;// values in vertex 
attribute vec2 inTexCoord;

void main()
{
//gl_ModelViewProjectionMatrix*
		vec4 vertex = vec4(inVertex,1) * scale ;
		mat4 LviewMatrix = gl_ModelViewProjectionMatrix;
		if (viewMatrix != mat4(1))
		LviewMatrix = viewMatrix ;
		
        gl_Position= LviewMatrix * transformation * vertex;
        color2=inColor;
		texCoord = inTexCoord ;
}