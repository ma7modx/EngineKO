#version 400
uniform vec3 color;// set its value 
varying vec3 color2;
varying vec2 texcoord;// common wth frag shader 
attribute vec3 vertex;
attribute vec3 inputcolor;// values in vertex 
attribute vec2 inputtexcoord;

void main()
{
//gl_ModelViewProjectionMatrix*
        gl_Position=gl_ModelViewProjectionMatrix*vec4(vertex,1.0);
        color2=vec3(inputcolor);
        texcoord=inputtexcoord;
}