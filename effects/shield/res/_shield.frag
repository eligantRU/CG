uniform sampler2D colormap;
uniform float intensity;

void main()
{
    vec4 texture = texture2D(colormap, gl_TexCoord[0].st);
    texture.a = intensity;
    gl_FragColor = 0.7 * texture;
}
