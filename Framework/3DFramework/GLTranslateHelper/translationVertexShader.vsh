uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;
uniform mat4 u_modelMatrix;

attribute vec4 a_vertex;

void main(void)
{
    gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_vertex;
}
