#version 400 

varying vec3 outColor;
varying vec2 outTexCoord;
uniform sampler2D tex ;
void main(){
    //gl_FragColor = vec4(1,0,1,1);
	gl_FragColor = texture2D(tex , outTexCoord);
}
