#version 400 

varying vec3 outColor;
varying vec2 outTexCoord;
varying bool outIsTexture;

uniform sampler2D tex ;
void main(){
    gl_FragColor = vec4(1,0,1,1);
	//if( outIsTexture == 1 )
	//gl_FragColor = texture2D(tex , outTexCoord);
}
