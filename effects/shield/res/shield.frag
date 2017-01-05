uniform sampler2D colormap;

void main()
{
    vec4 texture = texture2D(colormap, gl_TexCoord[0].st);
    texture.a = 0.7;
    gl_FragColor = 0.5 * texture;
}
