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
uniform sampler2D normalmap;
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

	vec4 DiffuseColor = color; // NOTE: reserved
	vec4 AmbientColor = color; // NOTE: reserved
	vec3 Falloff = vec3(1, 1, 1);
	vec3 NormalMap = texture2D(normalmap, fragTextureUV.st).rgb;
    
	//vec3 LightDir = vec3(LightPos.xy - (gl_FragCoord.xy / Resolution.xy), LightPos.z);
	vec3 LightDir = vec3(1, 1, 1); // TODO
	vec2 Resolution = vec2(1, 1); // TODO
	LightDir.x *= Resolution.x / Resolution.y;

	float D = length(LightDir);
	vec3 N = normalize(NormalMap * 2.0 - 1.0);
	vec3 L = normalize(LightDir);

	vec4 LightColor = vec4(1, 1, 1, 1); // NOTE: programming by contract
	vec3 Diffuse = (LightColor.rgb * LightColor.a) * max(dot(N, L), 0.0);

	vec3 Ambient = AmbientColor.rgb * AmbientColor.a;

	float Attenuation = 1.0 / (Falloff.x + (Falloff.y * D) + (Falloff.z * D * D));

	vec3 Intensity = Ambient + Diffuse * Attenuation;
	vec3 FinalColor = DiffuseColor.rgb * Intensity;
	gl_FragColor = color * vec4(FinalColor, 1.0) + 0.25 * diffuseIntensity + 0.35 * specularIntensity;
}
