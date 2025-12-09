// VERTEX

#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aUV;

out vec2 TexCoord;

uniform mat4 u_Projection;

void main() {
	gl_Position = u_Projection * vec4(aPos.xy, 0.0, 1.0);
    TexCoord = aUV;
}

// FRAGMENT
#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D text;
uniform vec4 u_Color;

void main() {
    float alpha = texture(text, TexCoord).r;
	FragColor = vec4(u_Color.rgb, u_Color.a * alpha);
}
