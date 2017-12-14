#SHADER VERTEX
#version 330 core
layout(location = 0) in vec4 position;

void main()
{
	gl_Position  = position;
};


#SHADER FRAGMENT
#version 330 core
layout(location = 0) out vec4 color;

uniform vec4 u_color;

void main()
{
	color  = vec4(1.0, 0.0, 0.0, 1.0);
	color  = u_color;
};
