#version 400

in vec3 normal0;

out vec4 fragColor;
uniform vec4 baseColor;
uniform vec3 ambLight;
uniform DirectionalLight directionalLight ;

struct BaseLight {
vec3 color;
float intensity;
};
struct DirectionalLight {
BaseLight base ;
vec3 direction ;
};

vec4 CalcLight(BaseLight base , vec3 direction , vec3 normal)
{
 float diffFactor = dot(-direction , normal);
 vec4 diffColor = vec4(0,0,0,0) ;
 
 if(diffFactor > 0)
 {
	diffColor = vec4(base.color , 1) * base.intensity * diffFactor ;
 }
 return diffColor ;
}
vec4 CalcDirectionalLight(DirectionalLight dlight , vec3 normal)
{
	return CalcLight(dlight.base , dlight.direction , normal) ;
}
void main()
{
	vec4 totLight = vec4(ambLight,1);
	vec4 color = vec4(baseColor,1);
	
	vec3 normal = normalize( normal0 );
	
	totLight += CalcLight(
	fragColor = color *totLight; 

}