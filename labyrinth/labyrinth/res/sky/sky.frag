#version 130

precision mediump float; 
precision mediump int;

struct LightSource
{
	vec4 position;
	vec4 diffuse;
	vec4 specular;
};

struct LightFactors
{
	float diffuse;
	float specular;
};

const float SHININESS = 10.0;

uniform LightSource light0;
uniform sampler2D colormap;
uniform mat4 view;

in vec2 fragTextureUV;
in vec3 fragNormal;
in vec3 fragViewDirection;

LightFactors GetLight0Factors()
{
	vec3 viewDirection = normalize(-fragViewDirection);
	vec3 fixedNormal = normalize(fragNormal);
	// Fix lightDirection for both directed and undirected light sources.
	vec3 delta = light0.position.w * viewDirection;
	vec4 lightPosInViewSpace = view * light0.position;
	vec3 lightDirection = normalize(lightPosInViewSpace.xyz + delta);

	vec3 reflectDirection = normalize(-reflect(lightDirection, fixedNormal));

	LightFactors result;
	result.diffuse = max(dot(fixedNormal, lightDirection), 0.0);
	float base = max(dot(reflectDirection, viewDirection), 0.0);
	result.specular = pow(base, SHININESS);

	result.diffuse = clamp(result.diffuse, 0.0, 1.0);
	result.specular = clamp(result.specular, 0.0, 1.0);

	return result;
}

void main()
{
	LightFactors factors = GetLight0Factors();
	vec4 color = texture2D(colormap, fragTextureUV.st);
	vec4 diffuseIntensity = color * light0.diffuse;
	vec4 specularIntensity = factors.specular * light0.specular; 

	gl_FragColor = 0.8 * diffuseIntensity + 0.2 * specularIntensity;
}
