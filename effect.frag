#version 120
 
uniform sampler2D tex;
 
void main() {
        vec4 color = texture2D(tex, gl_TexCoord[0].st);
        gl_FragColor = vec4(color.rgb, (color.a<=0.5) ? color.a : 1.0);
}
