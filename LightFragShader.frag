#version 400 

varying vec3 outColor; 
varying vec2 outTexCoord;
varying vec3 outLightSource ;
varying vec3 outNormal ;

uniform sampler2D tex ;

void main(){
	vec3 LightVector = normalize (outLightSource);
	vec3 ObjNormal = normalize (vec3(10,1,3));
	float LightForce = max(0 ,dot(LightVector , ObjNormal) );
	//if(LightForce > 90)
	
    //gl_FragColor = vec4(1,0,1,1);
	gl_FragColor = texture2D(tex , outTexCoord) * LightForce;
}