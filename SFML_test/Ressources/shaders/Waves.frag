#version 330 core

layout (location = 0) out vec4 color;

in DATA
{
	vec2 tc;
} fs_in;

uniform vec2 lightPos;
uniform vec2 Resolution = vec2(1.0, 1.0);
uniform vec3 LightColor;
uniform vec3 lightAttenuation;
uniform float radius;
uniform float ambiant;
uniform sampler2D tex;

void main ()
{
	//color = texture(tex, fs_in.tc);
	
	vec2 pixel=gl_FragCoord.xy;		
	pixel.y=Resolution.y-pixel.y;	
	vec2 aux=lightPos-pixel;
	float distance=length(aux);
	float attenuation=100.0*radius/(lightAttenuation.x+lightAttenuation.y*distance+lightAttenuation.z*distance*distance) + ambiant ;	
	vec4 color=vec4(attenuation,attenuation,attenuation,1.0)*vec4(LightColor,1.0);	
	color.a = 1.0;
	gl_FragColor = texture(tex, fs_in.tc)*color;
}