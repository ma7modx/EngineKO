#version 400 
uniform mat4 projection ;
 
varying vec3 color2; 
attribute vec3 vertex;
attribute vec3 inputcolor;// values in vertex 

void main()
{
//gl_ModelViewProjectionMatrix*
        gl_Position=gl_ModelViewProjectionMatrix*projection*vec4(vertex,1.0);
        color2=vec3(inputcolor);
}