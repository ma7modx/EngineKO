#version 400 

uniform sampler2D tex ;
varying vec3 outColor; 
varying vec2 outTexCoord;
varying vec3 outLightSource ;
varying vec3 outNormal ;
varying float outIsTexture;

void main(){
	//vec3 LightVector = normalize (outLightSource);
	//vec3 ObjNormal = normalize (outNormal);
	//float LightForce = max(0 ,dot(LightVector , ObjNormal) );
	
	vec4 Lcolor = texture2D(tex , outTexCoord) * outIsTexture ;
	vec4 Ltex = vec4(outColor,1) * (1.0 - outIsTexture);
	vec4 color = Lcolor + Ltex ;
	 gl_FragColor = color ;
}